#include "FirstReactionMethod.hpp"

void FirstReactionMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    SSA::initialization(model, maximumTime, initialTime, seed);
    //adds the method on filename
    methodOutName +="_FRM_output";
    //instantiates the tal array
    if (model->isModelLoaded())
        t = new double[model->getReacNumber()];
}
void FirstReactionMethod::perform(Model *model, double maximumTime, double initialTime, long int seed)
{
    cout << "-----------FIRST REACTION METHOD-----------" << endl;
    initialization(model, maximumTime, initialTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = initialTime;
    //performs the simulation
    calcPropensity();
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
void FirstReactionMethod::reacExecution()
{
    //updates the species quantities of the selected reaction
    updateSpeciesQuantities(selectedReaction);
}
void FirstReactionMethod::reacTimeGeneration()
{
    //generates the absolute time
    double u = 0.0;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i);
        u = ut->getRandomNumber();
        t[i] = (-1.0) * ut->ln(u) / propArray[i];
    }
}
void FirstReactionMethod::reacSelection()
{
    //selects the minimal time and updates the current time
    double minT = t[0];
    selectedReaction = 0;
    for (int i = 1; i < model->getReacNumber(); i++)
    {
        if (minT > t[i])
        {
            minT = t[i];
            selectedReaction = i;
        }
    }
    currentTime = currentTime + minT;
}
FirstReactionMethod::~FirstReactionMethod()
{
    //dtor
    delete[] t;
}
