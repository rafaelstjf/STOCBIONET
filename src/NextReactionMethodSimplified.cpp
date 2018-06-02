#include "../include/NextReactionMethodSimplified.hpp"

void NextReactionMethodSimplified::initialization(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    this->simulTime = simulTime;
    methodOutName = "NRMSIMP_output";
    model->loadModel(filename);
    if (model->isModelLoaded())
    {
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        timePropZero = new double[model->getReacNumber()];
        propNonZero = new double[model->getReacNumber()];
        delta = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        dg = new DependencyGraphNRM(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void NextReactionMethodSimplified::calcPropensity()
{
    int sum;
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
void NextReactionMethodSimplified::calcPropOne(int index)
{
    int sum = 1;
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
}
void NextReactionMethodSimplified::reacTimeGeneration()
{
    //generates the absolute time for each reaction and saves it in the priority queue
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {

        u = ut->getRandomNumber();
        delta[i] = (-1.00)*ut->ln(u);
        if(propArray[i] != 0.0)
            t1 = (delta[i] / propArray[i]) + currentTime;
        else
            t1 = inf;
        propNonZero[i] = propArray[i];
        queue->insertKey(i, t1);
    }
    //queue->sort();
}
void NextReactionMethodSimplified::reacSelection()
{
    //selects the node with the minimal time and updates the time
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();

}
void NextReactionMethodSimplified::reacExecution()
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
    //calculate the next time of the selected reacion
    if(propArray[sIndex] > 0.0)
    {
        u = ut->getRandomNumber();
        nt = (-1.0*ut->ln(u))/propArray[sIndex] + currentTime;
        propNonZero[sIndex] = propArray[sIndex];
        delta[sIndex] = propArray[sIndex]*nt;
    }
    else
    {
        propNonZero[sIndex] = (-1.0*propNonZero[sIndex]);
        delta[sIndex] = (-1.0*delta[sIndex]);
        nt = inf;
    }
    queue->update(selectedNode->getIndex(), nt);
    //uses the DG to update the time of the selected reaction on the priority Queue
    int *depArray = dg->getDependencies(selectedNode->getIndex());
    int depSize = dg->getDependenciesSize(selectedNode->getIndex());
    for (int i = 0; i < depSize; i++)
    {
        propOld = propArray[depArray[i]];
        calcPropOne(depArray[i]);
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
        queue->update(depArray[i], nt);
    }
}
void NextReactionMethodSimplified::perform(string filename, double simulTime, double beginTime)
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
    reacSelection();
    if(currentTime != inf)
    {
        currentTime = beginTime;
        while (currentTime <= simulTime)
        {
            xArray = new int[model->getSpecNumber()];
            for (int i = 0; i < model->getSpecNumber(); i++)
            {
                xArray[i] = specQuantity[i];
            }
            x.insert(make_pair(currentTime, xArray));
            reacSelection();
            reacExecution();
        }
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    printResult();
    saveToFile();
}
NextReactionMethodSimplified::~NextReactionMethodSimplified()
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
