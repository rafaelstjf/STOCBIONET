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
        dg = model->getDG();
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
            propNonZero[i] = EP;
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
    //cout << "Selected Node: " << selectedNode->getIndex() << " Current Time: " << currentTime << endl;
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
        int flag = 0;
        if (propArray[index] > EP)
        {
            if (index == sIndex)
            {
                u = ut->getRandomNumber();
                nt = ((-1 * ut->ln(u)) / propArray[index]) + currentTime;
            }
            else
            {
                if (propOld <= EP)
                {
                    if (propNonZero[index] <= EP)
                    {
                        u = ut->getRandomNumber();
                        nt = ((-1 * ut->ln(u)) / propArray[index]) + currentTime;
                        flag = 1;
                    }
                    else //was 0 before
                    {
                        nt = ((propNonZero[index] / propArray[index]) * (currentTime - timePropZero[index])) + currentTime;
                        flag = 2;
                        //cout << "Index: " << index << " NT: " << nt << " propArray[index]: " << propArray[index] << " propNonZero[index]: " << propNonZero[index] << " TimePropZero: " << timePropZero[i] << endl;
                    }
                }
                else
                {
                    nt = ((propOld / propArray[index]) * (queue->getNode(index)->getTime() - currentTime)) + currentTime;
                    //cout << "Index: " << index << " NT: " << nt << " propArray[index]: " << propArray[index] << " propOld: " << propOld << " Talfa: " << queue->getNode(index)->getTime() << endl;

                    flag = 3;
                }
                propNonZero[index] = propOld; //last propensity >0
            }
        }
        else
        {
            nt = INF;
            if (propOld > 0)
                timePropZero[index] = currentTime; //time that the propensity became 0
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
    if (currentTime < INF)
    {
        while (currentTime < maximumTime)
        {
            //cout << "Current Time: " << currentTime << endl;
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
