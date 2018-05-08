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
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
        queue = new IndexedPrioQueue(model->getReacNumber());
        dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
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
        t1 = (1.0 / propArray[i]) * ln(1.0 / u);
        queue->insertKey(i, t1);
    }
}
void NextReactionMethod::reacSelection()
{
    //selects the node with the minimal time and updates the time
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();
}
void NextReactionMethod::reacExecution()
{
    double u;
    double nt;
    //updates the species quantities
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[selectedReaction][i];
    }
    //uses the DG to update the time of the selected reaction on the priority Queue
    int *depArray = dg->getDependencies(selectedNode->getIndex());
    int depSize = dg->getDependenciesSize(selectedNode->getIndex());
    for (int i = 0; i < depSize; i++)
    {
        double propOld = propArray[depArray[i]];
        u = ut->getRandomNumber();
        calcPropOne(depArray[i]);
        if (depArray[i] != selectedNode->getIndex())
        {
            nt = ((propOld / propArray[depArray[i]]) * (selectedNode->getTime() - currentTime) + currentTime);
        }
        else
        {
            nt = (ln((1.0 / u) / propArray[depArray[i]]) + currentTime);
        }
        queue->update(depArray[i], nt);
    }
}
void NextReactionMethod::peform(string filename, double simulTime)
{
    cout << "NEXT REACTION METHOD" << endl;
    initialization(filename, simulTime);
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = 0.0;
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
    //printResult();
    saveToFile();
}
void NextReactionMethod::~NextReactionMethod()
{
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
    delete queue;
    delete selectedNode;
}