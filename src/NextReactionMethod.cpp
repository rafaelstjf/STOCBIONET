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
        //it needs to use the DG without the self edge
        dg = new DependencyGraph(false, model);
    }
}
void NextReactionMethod::reacTimeGeneration()
{
    double u, nt;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i); //uses calcPropOne(i) to saves one O(n)
        if (propArray[i] <= EP)
        {
            nt = INF;
        }
        else
        {
            u = ut->getRandomNumber();
            nt = ((-1 * ut->ln(u)) / propArray[i]) + currentTime;
        }
        propNonZero[i] = propArray[i]; //if propNonZero[i] == 0 it happened since the beginning
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
    double delta;
    int index;
    int sIndex = selectedNode->getIndex();
    updateSpeciesQuantities(sIndex);
    calcPropOne(sIndex);
    if (propArray[sIndex] <= EP)
    {
        nt = INF;
    }
    else
    {
        u = ut->getRandomNumber();
        nt = ((-1 * ut->ln(u)) / propArray[sIndex]) + currentTime;
    }
    propNonZero[sIndex] = propArray[sIndex];
    queue->update(sIndex, nt);
    int *depArray = dg->getDependencies(sIndex);
    int depSize = dg->getDependenciesSize(sIndex);
    for (int i = 0; i < depSize; i++)
    {
        index = depArray[i];
        propOld = propArray[index];
        calcPropOne(index);
        if (propArray[index] > EP)
        {
            if (propOld <= EP) //propensity changed from 0
            {
                if (propNonZero[index] > EP) //the propensity was >0 at a moment t
                    delta = propNonZero[index] * (currentTime - timePropZero[index]);
                else //propensity was 0 from the beginning but now it's >0
                {
                    u = ut->getRandomNumber();
                    delta = (-1 * ut->ln(u)); //propNonZero == 0
                }
            }
            else //propOld > 0, so propNonZero > 0
                delta = propNonZero[index] * (queue->getNode(index)->getTime() - currentTime);
            nt = delta / propArray[index] + currentTime;
            propNonZero[index] = propArray[index]; //saves the last propensity different than 0
        }
        else
        {
            if (propNonZero[index] > EP)
                timePropZero[index] = currentTime;
            nt = INF;
        }
        queue->update(index, nt);
    }
    delete[] depArray;
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
    if (currentTime != INF)
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
