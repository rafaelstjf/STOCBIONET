#include "../include/ModifiedNextReactionMethod.hpp"

void ModifiedNextReactionMethod::initialization(string filename, double simulTime)
{
    sucess = false;
    model = new Model();
    ut = new Utils();
    this->simulTime = simulTime;
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_MNRM_output";
            break;
        }
        else
            methodOutName += filename[i];
    }
    model->loadModel(filename);
    if (model->isModelLoaded())
    {
        log = new Log(model->getSpecNumber());
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        //
        P = new double[model->getReacNumber()];
        T = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
    reacCount = 0;
    reacPerSecond = 0.0;
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
        t1 = (P[i] - T[i]) / propArray[i];
        queue->insertKey(i, t1);
    }
}
void ModifiedNextReactionMethod::reacSelection()
{
    selectedNode = queue->getMin();
    currentTime = currentTime + selectedNode->getTime();
}
void ModifiedNextReactionMethod::reacExecution()
{
    double u;  //random number
    double nt; //new time
    int index;
    int sIndex = selectedNode->getIndex();
    //updates the species quantities
    updateSpeciesQuantities(sIndex);
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        T[i] = T[i] + propArray[i] * selectedNode->getTime();
    }
    u = ut->getRandomNumber();
    P[sIndex] = P[sIndex] + (-1.0 * ut->ln(u));
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i);
        nt = (P[i] - T[i]) / propArray[i];
        queue->update(i, nt);
    }
}
void ModifiedNextReactionMethod::perform(string filename, double simulTime, double beginTime)
{
    cout << "MODIFIED NEXT REACTION METHOD" << endl;
    initialization(filename, simulTime);
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = beginTime;
    //calculates the propensity of all the reactions and generates the simulation time
    reacTimeGeneration();
    //saves the species quantities on beginTime
    reacSelection();
    if (currentTime != inf)
    {
        currentTime = beginTime;
        //currentTime = beginTime;
        while (currentTime <= simulTime)
        {
            log->insertNode(currentTime, specQuantity);
            reacSelection();
            reacExecution();
        }
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    sucess = true;
    reacPerSecond = (double)reacCount/(en-beg);
    cout << "Reactions per second: " << reacPerSecond << endl;
    saveToFile();
}
ModifiedNextReactionMethod::~ModifiedNextReactionMethod()
{
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
    delete[] T;
    delete[] P;
    delete queue;
    delete selectedNode;
    delete log;
}
