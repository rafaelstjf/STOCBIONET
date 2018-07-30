#include "../include/FirstReactionMethod.hpp"

void FirstReactionMethod::initialization(string filename, double simulTime, long int seed)
{
    //instantiates the variables
    model = new Model();
    if (seed >= 0)
        ut = new Utils(seed); //instantiates the utility class
    else
        ut = new Utils(); //instantiates the utility class    model->loadModel(filename);
    sucess = false;
    this->simulTime = simulTime;
    reacCount = 0;
    reacPerSecond = 0.0;
    //creates the output file's name
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_FRM_output";
            break;
        }
        else
            methodOutName += filename[i];
    }
    //loads both log, the depedency graph and the tal array
    if (model->isModelLoaded())
    {
        log = new Log(model->getSpecNumber());
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        t = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void FirstReactionMethod::perform(string filename, double simulTime, double beginTime, long int seed)
{
    cout << "-----------FIRST REACTION METHOD-----------" << endl;
    initialization(filename, simulTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = beginTime;
    //performs the simulation
    calcPropensity();
    while (currentTime <= simulTime)
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
