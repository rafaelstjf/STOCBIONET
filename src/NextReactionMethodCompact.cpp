#include "../include/NextReactionMethodCompact.hpp"

void NextReactionMethodCompact::initialization(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    this->simulTime = simulTime;
      for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_NRMCOMPACT_output";
            break;
        }

        else
            methodOutName += filename[i];
    }
    model->loadModel(filename);
    if (model->isModelLoaded())
    {
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        timePropZero = new double[model->getReacNumber()];
        propNonZero = new double[model->getReacNumber()];
        delta = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void NextReactionMethodCompact::calcPropensity()
{
    double sum;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 1;
        for (int j = 0; j < model->getSpecNumber(); j++)
        {
            sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[i][j]);
        }
        propArray[i] = model->getReacRateArray()[i] * sum;
    }
}
void NextReactionMethodCompact::calcPropOne(int index)
{
    double sum = 1;
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
}
void NextReactionMethodCompact::reacTimeGeneration()
{
    //generates the absolute time for each reaction and saves it in the priority queue
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {

        u = ut->getRandomNumber();
        delta[i] = (-1.00)*ut->ln(u);
        if(propArray[i] > 0.0)
            t1 = (delta[i] / propArray[i]) + currentTime;
        else
            t1 = inf;
        propNonZero[i] = propArray[i]; //if propArray[i] = propNonZero[i] = 0, that happens since the beginning of the simulation
        queue->insertKey(i, t1);
    }
    //queue->sort();
}
void NextReactionMethodCompact::reacSelection()
{
    //selects the node with the minimal time and updates the time
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();

}
void NextReactionMethodCompact::reacExecution()
{
    double u; //random number
    double nt; //new time
    double propOld;
    int sIndex = selectedNode->getIndex();
    for(int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[sIndex][i];
    }
    calcPropOne(sIndex);
    u = ut->getRandomNumber();
    delta[sIndex] = (-1.0*ut->ln(u));
    propNonZero[sIndex] = 0;
    //uses the DG to update the time of the selected reaction on the priority Queue
    int *depArray = dg->getDependencies(sIndex);
    int depSize = dg->getDependenciesSize(sIndex);
    for (int i = 0; i < depSize; i++)
    {
        propOld = propArray[depArray[i]];
        calcPropOne(depArray[i]);
        nt = inf;
        if(propArray[depArray[i]] > 0.0)
        {
            nt = (delta[depArray[i]] - (propNonZero[depArray[i]]*currentTime))/propArray[depArray[i]] + currentTime;
            propNonZero[depArray[i]] = propArray[depArray[i]];
            delta[depArray[i]] = propArray[depArray[i]]*nt;
        }
        else if(propOld > 0.0)
        {
            propNonZero[depArray[i]] = (-1.0*propOld);
            delta[depArray[i]] = propOld*currentTime;
        }
        //if both propensities(last and current) are 0 so nt = inf
        queue->update(depArray[i], nt);
    }

}
void NextReactionMethodCompact::perform(string filename, double simulTime, double beginTime)
{
    cout << "NEXT REACTION METHOD SIMPLIFIED" << endl;
    initialization(filename, simulTime);
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = beginTime;
    int *xArray;
    x.clear();
    calcPropensity();
    //reacTimeGeneration comes before the while because you can calculate it only once and then
    //update inside the while
    reacTimeGeneration();
    //saves the species quantities on beginTime
    xArray = new int[model->getSpecNumber()];
    for (int i = 0; i < model->getSpecNumber(); i++)
        xArray[i] = specQuantity[i];
    x.insert(make_pair(currentTime, xArray));
    reacSelection();
    if(currentTime != inf)
    {
        //currentTime = beginTime;
        while (currentTime <= simulTime)
        {
            reacExecution();
              xArray = new int[model->getSpecNumber()];
            for (int i = 0; i < model->getSpecNumber(); i++)
            {
                xArray[i] = specQuantity[i];
            }
            x.insert(make_pair(currentTime, xArray));
            reacSelection();
        }
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    saveToFile();
}
NextReactionMethodCompact::~NextReactionMethodCompact()
{
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
    delete[] delta;
    delete queue;
    delete selectedNode;
}
