#include "SimplifiedNextReactionMethod.hpp"

void SimplifiedNextReactionMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    SSA::initialization(model, maximumTime, initialTime, seed);
    methodOutName += "_SNRM_output";
    if (model->isModelLoaded())
    {
        queue = new IndexedPrioQueue(model->getReacNumber());
        dg = model->getDG();
        P = new double[model->getReacNumber()];
        U = new double[model->getReacNumber()];
        T = new double[model->getReacNumber()];
    }
}
void SimplifiedNextReactionMethod::reacTimeGeneration()
{
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i);
        u = ut->getRandomNumber();
        P[i] = (-1.0 * ut->ln(u));
        U[i] = currentTime;
        T[i] = 0.0;
        t1 = (P[i] - T[i]) / propArray[i] + currentTime;
        queue->insertKey(i, t1);
    }
}
void SimplifiedNextReactionMethod::reacSelection()
{
    //selects the node with the minimal time and updates the time
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();
}
void SimplifiedNextReactionMethod::reacExecution()
{
    double u;  //random number
    double nt; //new time
    int index;
    int sIndex = selectedNode->getIndex();
    //updates the species quantities
    updateSpeciesQuantities(sIndex);
    u = ut->getRandomNumber();
    P[sIndex] = P[sIndex] + (-1.0 * ut->ln(u));
    int *depArray = dg->getDependencies(sIndex);
    int depSize = dg->getDependenciesSize(sIndex);
    for (int i = 0; i < depSize; i++)
    {
        index = depArray[i];
        T[index] = T[index] + propArray[index] * (currentTime - U[index]);
        U[index] = currentTime;
        calcPropOne(index);
        nt = ((P[index] - T[index]) / propArray[index]) + currentTime;
        queue->update(index, nt);
    }
    delete[] depArray;
}
void SimplifiedNextReactionMethod::perform(Model *model, double maximumTime, double initialTime, long int seed)
{
    cout << "-----------SIMPLIFIED NEXT REACTION METHOD-----------" << endl;
    initialization(model, maximumTime, initialTime, seed);
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = initialTime;
    //calculates the propensity of all the reactions and generates the simulation time
    reacTimeGeneration();
    //saves the species quantities on initialTime
    reacSelection();
    if (currentTime != inf)
    {
        currentTime = initialTime;
        //currentTime = initialTime;
        while (currentTime <= maximumTime)
        {
            log->insertNode(currentTime, specQuantity);
            reacSelection(); //selects a reaction
            reacExecution(); //executes the selected reaction
        }
    }
    double en = ut->getCurrentTime(); //end
    postSimulation((en - beg));
}
SimplifiedNextReactionMethod::~SimplifiedNextReactionMethod()
{
    delete[] T;
    delete[] U;
    delete[] P;
    delete queue;
    delete selectedNode;
}
