#include "../include/NextReactionMethod.hpp"

void NextReactionMethod::initialization(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    this->simulTime = simulTime;
    methodOutName = "NRM_output";
    model->loadModel(filename);
    if (model->isModelLoaded())
    {
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        RNArray = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
        queue = new List(model->getReacNumber());
        dg = new DependencyGraphNRM(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        dg->printGraph();
    }
}
void NextReactionMethod::calcPropensity()
{
    int sum = 1;
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
void NextReactionMethod::calcPropOne(int index)
{
    int sum = 1;
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
}
void NextReactionMethod::reacTimeGeneration()
{
    //generates the absolute time for each reaction and saves it in the priority queue
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {

        u = ut->getRandomNumber();
        RNArray[i] = (-1.00)*ut->ln(u);
        if(propArray[i] != 0.0)
            t1 = (RNArray[i] / propArray[i]) ;
        else
            t1 = inf;
        queue->insertKey(i, t1);
    }
    queue->sort();
}
void NextReactionMethod::reacSelection()
{
    //selects the node with the minimal time and updates the time
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();

}
void NextReactionMethod::reacExecution()
{
    double u; //random number
    double nt; //new time
    //updates the species quantities
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[selectedNode->getIndex()][i];
    }
    //calculate the next time of the selected reacion
    calcPropOne(selectedNode->getIndex());

    if(propArray[selectedNode->getIndex()] != 0.0)
    {
        u = ut->getRandomNumber();
        RNArray[selectedNode->getIndex()] = (-1.00)*ut->ln(u);
        nt = ((RNArray[selectedNode->getIndex()] / propArray[selectedNode->getIndex()]) + currentTime);
    }
    else
        nt = inf;
    queue->update(selectedNode->getIndex(), nt);
    //uses the DG to update the time of the selected reaction on the priority Queue
    int *depArray = dg->getDependencies(selectedNode->getIndex());
    int depSize = dg->getDependenciesSize(selectedNode->getIndex());
    for (int i = 0; i < depSize; i++)
    {
        double propOld = propArray[depArray[i]];
        calcPropOne(depArray[i]);
        if(propArray[depArray[i]] != 0.0)
        {
            nt = RNArray[depArray[i]]/propArray[depArray[i]] + currentTime;
            //t[i] = -ln(r)/ak +
        }
        else
            nt = inf;
        queue->update(depArray[i], nt);
    }
}
void NextReactionMethod::perform(string filename, double simulTime, double beginTime)
{
    cout << "NEXT REACTION METHOD" << endl;
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
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    printResult();
    saveToFile();
}
NextReactionMethod::~NextReactionMethod()
{
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
    delete[] RNArray;
    delete queue;
    delete selectedNode;
}
