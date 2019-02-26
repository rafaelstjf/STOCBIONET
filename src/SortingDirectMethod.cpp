#include "SortingDirectMethod.hpp"

void SortingDirectMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    //instantiates the variables
    SSA::initialization(model, maximumTime, initialTime, seed);
    methodOutName += "_SDM_output";
    if (model->isModelLoaded())
    {
        reactionSO = new int[model->getReacNumber()]; //creates an array to sort the most used reactions
        dg = new DependencyGraph(true, model);
        for (int i = 0; i < model->getReacNumber(); i++)
        {
            reactionSO[i] = i;
        }
    }
}
void SortingDirectMethod::reacTimeGeneration()
{
    double u1;
    u1 = ut->getRandomNumber();
    t = (-1.0 * ut->ln(u1)) / totalPropensity;
}
void SortingDirectMethod::reacSelection()
{
    double selector;
    double u2;
    int reactionSOindex;
    u2 = ut->getRandomNumber();
    if (totalPropensity <= EP)
        selectedReaction = -1;
    else
    {

        selector = totalPropensity * u2;
        for (int i = 0; i < model->getReacNumber(); i++)
        {
            selector = selector - propArray[reactionSO[i]];
            if (selector <= EP)
            {
                reactionSOindex = i;
                selectedReaction = reactionSO[i];
                break;
            }
        }
    }
}
void SortingDirectMethod::reacExecution()
{
    if (selectedReaction == -1)
    {
        currentTime = INF;
        return;
    }
    updateSpeciesQuantities(selectedReaction);
    if (reactionSOindex != 0)
    {
        //moves the reaction index to a position ahead on the array
        int temp = reactionSO[reactionSOindex];
        reactionSO[reactionSOindex] = reactionSO[reactionSOindex - 1];
        reactionSO[reactionSOindex] = temp;
    }
    int *depArray = dg->getDependencies(selectedReaction);
    int depSize = dg->getDependenciesSize(selectedReaction);
    for (int i = 0; i < depSize; i++)
    {
        calcPropOne(depArray[i]);
    }
    delete[] depArray;
    currentTime = currentTime + t;
}
void SortingDirectMethod::perform(Model *model, double maximumTime, double initialTime, long int seed)
{
    cout << "-----------SORTING DIRECT METHOD-----------" << endl;
    initialization(model, maximumTime, initialTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = initialTime;
    //peforms the simulation
    calcPropensity(); //calculate the reactions propensity
    while (currentTime < maximumTime)
    {
        //saves the current species quantities on the log
        log->insertNode(currentTime, specQuantity);
        //generates simulation time
        reacTimeGeneration();
        //reaction's selection
        reacSelection();
        //reaction's execution
        reacExecution();
    }
    double en = ut->getCurrentTime(); //ending of the simulation
    sucess = true;
    reacPerSecond = (double)reacCount / (en - beg);
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    cout << "Reactions per second: " << reacPerSecond << endl;
    log->setReacPerSecond(reacPerSecond);
    log->setNumberReacExecuted(reacCount);
}
SortingDirectMethod::~SortingDirectMethod()
{
    delete[] reactionSO;
}