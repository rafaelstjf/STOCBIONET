#include "NextReactionMethod.hpp"

void NextReactionMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    //instantiates the variables
    SSA::initialization(model, maximumTime, initialTime, seed);
    methodOutName += "_NRM_output";
    //loads both log and the depedency graph
    if (model->isModelLoaded())
    {
        timePropZero = new double[model->getReacNumber()];
        propNonZero = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        t0 = new double[model->getReacNumber()];
        //it needs to use the DG without the self edge
        dg = model->getDGNoSelfEdge();
    }
}
void NextReactionMethod::reacTimeGeneration()
{
    double u, nt;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        t0[i] = -1;
        calcPropOne(i); //uses calcPropOne(i) to saves one O(n)
        if (propArray[i] <= EP)
        {
            nt = INF;
            propNonZero[i] = 0;
        }
        else
        {
            propNonZero[i] = propArray[i]; //if propNonZero[i] == 0 it happened since the beginning
            u = ut->getRandomNumber();
            nt = ((-1 * ut->ln(u)) / propArray[i]) + currentTime;
        }
        timePropZero[i] = 0;
        queue->insertKey(i, nt);
    }
}
void NextReactionMethod::reacSelection()
{
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();
}
void NextReactionMethod::reacExecution()
{
    double u;
    double nt;
    double propOld;
    int index;
    int sIndex = selectedNode->getIndex();
    updateSpeciesQuantities(sIndex);
    int *depArray = dg->getDependencies(sIndex);
    int depSize = dg->getDependenciesSize(sIndex);
    for (int i = 0; i < depSize; i++)
    {
        index = depArray[i];
        propOld = propArray[index];
        calcPropOne(index);
        if (propArray[index] <= EP) //propensity is 0
        {
            nt = INF;
            if (t0[index] == -1)
                t0[index] = currentTime;
        }
        else //propensity > 0
        {
            if (propOld <= EP) //was 0 before
            {
                if (propNonZero[index] > EP)
                    nt = ((propNonZero[index] / propArray[index]) * (timePropZero[index]) - t0[index]) + currentTime;
                else //it has never been >0
                {
                    u = ut->getRandomNumber();
                    nt = ((-1 * ut->ln(u)) / propArray[index]) + currentTime;
                }
            }
            else
            {
                nt = ((propOld / propArray[index]) * (queue->getNode(index)->getTime() - currentTime)) + currentTime;
                propNonZero[index] = propOld; //last propensity >0
                timePropZero[index] = nt;     //time that the propensity became 0
            }
            t0[index] = -1;
        }
        queue->update(index, nt);
    }
    delete[] depArray;
    propOld = propArray[sIndex];
    calcPropOne(sIndex);
    if (propArray[sIndex] <= EP)
    {
        propNonZero[sIndex] = propOld;
        timePropZero[sIndex] = currentTime;
        nt = INF;
    }
    else
    {
        t0[sIndex] = -1;
        u = ut->getRandomNumber();
        nt = ((-1 * ut->ln(u)) / propArray[sIndex]) + currentTime;
    }
    queue->update(sIndex, nt);
}
void NextReactionMethod::perform(Model *model, double maximumTime, double initialTime, long int seed)
{
    cout << "-----------NEXT REACTION METHOD-----------" << endl;
    initialization(model, maximumTime, initialTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = initialTime;
    //calculates the propensity of all the reactions and generates the simulation time
    reacTimeGeneration();
    //saves the species quantities on initialTime
    log->insertNode(currentTime, specQuantity);
    reacSelection(); //just to check if the time = inf
    if (currentTime < INF)
    {
        while (currentTime < maximumTime)
        {
            reacExecution(); //executes the reaction
            //saves the species quantities
            log->insertNode(currentTime, specQuantity);
            //selects a new reaction
            reacSelection();
        }
        log->insertNode(currentTime, specQuantity);
    }
    double en = ut->getCurrentTime(); //ending of the simulation
    postSimulation((en - beg));
}
NextReactionMethod::~NextReactionMethod()
{
    delete[] propNonZero;
    delete[] timePropZero;
    delete queue;
    delete selectedNode;
}
