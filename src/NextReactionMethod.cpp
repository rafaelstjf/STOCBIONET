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
        propArrayNonZero = new double[model->getReacNumber()];
        RNArray = new double[model->getReacNumber()];
        timePropZero = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
        queue = new List(model->getReacNumber());
        dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
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
        if(propArray[i] > 0)
            propArrayNonZero[i] = propArray[i];
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
    if(propArray[index] > 0)
        propArrayNonZero[index] = propArray[index];
}
void NextReactionMethod::reacTimeGeneration()
{
    //generates the absolute time for each reaction and saves it in the priority queue
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        u = ut->getRandomNumber();
        t1 = (1.0 / propArray[i]) * ut->ln(1.0 / u);
        if(propArray[i]==0)
        {
            timePropZero[i] = currentTime;
            t1 = INT_MAX;
            if(currentTime == 0)  //saves the random number in the beginning of the simulation
            {
                RNArray[i] = u;
            }
        }

        queue->insertKey(i, t1);


    }
    queue->print();
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
    //uses the DG to update the time of the selected reaction on the priority Queue
    int *depArray = dg->getDependencies(selectedNode->getIndex());
    int depSize = dg->getDependenciesSize(selectedNode->getIndex());
    for (int i = 0; i < depSize; i++)
    {
        double propOld = propArray[depArray[i]];
        calcPropOne(depArray[i]);
        HeapNode* actualNode = queue->getNode(depArray[i]);
        if (depArray[i] != selectedNode->getIndex())
        {
            if(propArray[depArray[i]] > 0 && propOld == 0)
            {
                if(timePropZero[depArray[i]] == 0)  //if the reaction started the simulation with propensity = 0;
                    nt = ((ut->ln(1.0 / RNArray[depArray[i]]) / propArray[depArray[i]]) + currentTime);
                else
                    nt = ((propArrayNonZero[depArray[i]] / propArray[depArray[i]]) * (actualNode->getTime() - timePropZero[depArray[i]]) + currentTime);

            }
            else
            {
                if(propArray[depArray[i]] == 0)
                    nt = INT_MAX;
                else
                    nt = ((propOld / propArray[depArray[i]]) * (actualNode->getTime() - currentTime) + currentTime);
            }

        }
        else
        {
            if(propArray[depArray[i]] == 0)
                nt = INT_MAX;
            else
            {
                u = ut->getRandomNumber();
                nt = ((ut->ln(1.0 / u) / propArray[depArray[i]]) + currentTime);
            }
        }
        if(nt == INT_MAX)
            timePropZero[depArray[i]] = currentTime;
        queue->update(depArray[i], nt);
    }
}
void NextReactionMethod::perform(string filename, double simulTime)
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
    delete[] propArrayNonZero;
    delete[] RNArray;
    delete[] timePropZero;
    delete queue;
    delete selectedNode;
}
