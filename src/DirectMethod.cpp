#include "DirectMethod.hpp"
void DirectMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    SSA::initialization(model, maximumTime, initialTime, seed);
    //creates the output file's name
    methodOutName += "_DM_output";
    //loads both log and the depedency graph
    if (model->isModelLoaded())
        dg = model->getDG();
}
void DirectMethod::reacTimeGeneration()
{
    double u1;
    u1 = ut->getRandomNumber();
    t = (-1.0 * ut->ln(u1)) / totalPropensity; //next time increases
}
void DirectMethod::reacSelection()
{
    double selector;
    double u2;
    u2 = ut->getRandomNumber();
    if (totalPropensity <= EP)
        selectedReaction = -1;
    else
    {

        selector = totalPropensity * u2;
        for (int i = 0; i < model->getReacNumber(); i++)
        {
            selector = selector - propArray[i];
            if (selector <= EP)
            {
                selectedReaction = i;
                break;
            }
        }
    }
}
void DirectMethod::reacExecution()
{
    if (selectedReaction == -1)
    {
        currentTime = INF;
        return;
    }
    updateSpeciesQuantities(selectedReaction);
    //check the dependencies of the selected reaction and update the propensity array
    int *depArray = dg->getDependencies(selectedReaction);
    int depSize = dg->getDependenciesSize(selectedReaction);
    for (int i = 0; i < depSize; i++)
    {
        calcPropOne(depArray[i]);
    }
    delete[] depArray;
    currentTime = currentTime + t;
}
void DirectMethod::perform(Model *model, double maximumTime, double initialTime, long int seed)
{
    cout << "-----------DIRECT METHOD-----------" << endl;
    initialization(model, maximumTime, initialTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = initialTime;
    t = 0.0;
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
    postSimulation((en-beg));
}
DirectMethod::~DirectMethod()
{
}
