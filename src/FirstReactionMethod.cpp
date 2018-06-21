#include "../include/FirstReactionMethod.hpp"

void FirstReactionMethod::initialization(string filename, double simulTime)
{
    sucess = false;
    model = new Model();
    ut = new Utils();
    model->loadModel(filename);
    this->simulTime = simulTime;
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
    if (model->isModelLoaded())
    {
        log = new Log(model->getSpecNumber());
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
        t = new double[model->getReacNumber()];
    }
    reacCount = 0;
    reacPerSecond = 0.0;
}
void FirstReactionMethod::perform(string filename, double simulTime, double beginTime)
{
    cout << "FIRST REACTION METHOD" << endl;
    initialization(filename, simulTime);
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = beginTime;
    calcPropensity();
    while (currentTime <= simulTime)
    {
       log->insertNode(currentTime, specQuantity);
        //generate simulation time
        reacTimeGeneration();
        //reaction selection
        reacSelection();
        //reaction execution
        reacExecution();
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    sucess = true;
    reacPerSecond = (double)reacCount/(en-beg);
    cout << "Reactions per second: " << reacPerSecond << endl;
    log->setReacPerSecond(reacPerSecond);
    log->setNumberReacExecuted(reacCount);
    saveToFile();
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
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
    delete[] t;
    delete log;
}
