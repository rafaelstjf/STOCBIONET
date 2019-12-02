#include "ModifiedNextReactionMethod.hpp"

void ModifiedNextReactionMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    //instantiates the variables
    SSA::initialization(model, maximumTime, initialTime, seed);
    //creates the output file's name
    methodOutName += "_MNRM_output";
    //loads both log and the depedency graph
    if (model->isModelLoaded())
    {
        dg = model->getDG();
        P = new double[model->getReacNumber()];
        T = new double[model->getReacNumber()];
        dT = new double[model->getReacNumber()];
    }
}
void ModifiedNextReactionMethod::reacTimeGeneration()
{
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i);
        u = ut->getRandomNumber();
        P[i] = (-1.0 * ut->ln(u));
        T[i] = 0.0;
    }
}
void ModifiedNextReactionMethod::reacSelection()
{
    double minDT = INF;
    selectedReaction = -1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        dT[i] = (P[i] - T[i]) / propArray[i];
        if (minDT > dT[i])
        {
            minDT = dT[i];
            selectedReaction = i;
        }
    }
}
void ModifiedNextReactionMethod::reacExecution()
{
    if (selectedReaction == -1)
    {
        currentTime = INF;
        return;
    }
    double u; //random number
    //updates the species quantities
    updateSpeciesQuantities(selectedReaction);
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        T[i] = T[i] + propArray[i] * dT[selectedReaction];
    }
    u = ut->getRandomNumber();
    P[selectedReaction] = P[selectedReaction] + (-1.0 * ut->ln(u));
    currentTime = currentTime + dT[selectedReaction];
    int *depArray = dg->getDependencies(selectedReaction);
    int depSize = dg->getDependenciesSize(selectedReaction);
    for (int i = 0; i < depSize; i++)
    {
        calcPropOne(depArray[i]);
    }
    delete[] depArray;
}
void ModifiedNextReactionMethod::perform(Model *model, double maximumTime, double initialTime, long int seed)
{
    cout << "-----------MODIFIED NEXT REACTION METHOD-----------" << endl;
    initialization(model, maximumTime, initialTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    //performs the simulation
    currentTime = initialTime;
    //calculates the propensity of all the reactions and generates the simulation time
    reacTimeGeneration();
    while (currentTime < maximumTime)
    {
        log->insertNode(currentTime, specQuantity);
        reacSelection();
        reacExecution();
    }
    double en = ut->getCurrentTime(); //ending of the simulation
    postSimulation((en - beg));
}
ModifiedNextReactionMethod::~ModifiedNextReactionMethod()
{
    delete[] T;
    delete[] P;
    delete[] dT;
}
