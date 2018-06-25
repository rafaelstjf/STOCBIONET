#include "../include/NextReactionMethod.hpp"

void NextReactionMethod::initialization(string filename, double simulTime)
{
    //instantiates the variables
    sucess = false;
    model = new Model();
    ut = new Utils();
    this->simulTime = simulTime;
    model->loadModel(filename);
    reacCount = 0;
    reacPerSecond = 0.0;
    //creates the output file's name
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_NRM_output";
            break;
        }
        else
            methodOutName += filename[i];
    }
    //loads both log and the depedency graph
    if (model->isModelLoaded())
    {
        log = new Log(model->getSpecNumber());
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        timePropZero = new double[model->getReacNumber()];
        propNonZero = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        dg = new DependencyGraphNRM(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void NextReactionMethod::reacTimeGeneration()
{
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i); //uses calcPropOne(i) to saves one O(n)
        if (propArray[i] == 0.0)
        {
            t1 = inf;
        }
        else
        {
            u = ut->getRandomNumber();
            t1 = ((-1 * ut->ln(u)) / propArray[i]) + currentTime;
        }
        propNonZero[i] = propArray[i]; //if propNonZero[i] == 0 it happened since the beginning
        queue->insertKey(i, t1);
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
    if (propArray[sIndex] == 0.0)
    {
        nt = inf;
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
        if (propArray[index] > 0.0)
        {
            if (propOld == 0.0) //propensity changed from 0
            {
                if (propNonZero[index] > 0.0) //the propensity was >0 at a moment t
                    delta = propNonZero[index] * (currentTime - timePropZero[index]);
                else //propensity was 0 from the beginning but now it's >0
                {
                    u = ut->getRandomNumber();
                    delta = (-1 * ut->ln(u)); //propNonZero == 0
                }
            }
            else //propOld > 0, so propNonZero > 0
                delta = propNonZero[index] * (selectedNode->getTime() - currentTime);
            nt = delta / propArray[index] + currentTime;
            propNonZero[index] = propArray[index]; //saves the last propensity different than 0
        }
        else
        {
            if (propNonZero[index] > 0.0)
                timePropZero[index] = currentTime;
            nt = inf;
        }
        queue->update(index, nt);
    }
    delete [] depArray;
}
void NextReactionMethod::perform(string filename, double simulTime, double beginTime)
{
    cout << "NEXT REACTION METHOD" << endl;
    initialization(filename, simulTime);//instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();//beginning of the simulation
    currentTime = beginTime;
    //calculates the propensity of all the reactions and generates the simulation time
    reacTimeGeneration();
    //saves the species quantities on beginTime
    log->insertNode(currentTime, specQuantity);
    reacSelection(); //just to check if the time = inf
    if (currentTime != inf)
    {
        while (currentTime <= simulTime)
        {
            reacExecution(); //executes the reaction
            //saves the species quantities
            log->insertNode(currentTime, specQuantity);
            //selects a new reaction
            reacSelection();
        }
    }
    double en = ut->getCurrentTime(); //ending of the simulation
    sucess = true;
    reacPerSecond = (double)reacCount/(en-beg);
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    cout << "Reactions per second: " << reacPerSecond << endl;
    log->setReacPerSecond(reacPerSecond);
    log->setNumberReacExecuted(reacCount);
    saveToFile();
}
NextReactionMethod::~NextReactionMethod()
{
    delete dg;
    delete model;
    delete ut;
    delete[] propNonZero;
    delete[] propArray;
    delete[] timePropZero;
    delete queue;
    delete selectedNode;
    delete log;
}
