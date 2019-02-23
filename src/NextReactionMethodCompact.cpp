#include "../include/NextReactionMethodCompact.hpp"

void NextReactionMethodCompact::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    sucess = false;
    this->model = model;
    if (seed >= 0)
        ut = new Utils(seed); //instantiates the utility class
    else
        ut = new Utils(); //instantiates the utility class    this->maximumTime = maximumTime;
    string filename = model->getFilename();
    reacCount = 0;
    reacPerSecond = 0.0;
    //creates the output file's name
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_NRMC_output";
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
        delta = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        //it needs to use the DG without the self edge
        dg = new DependencyGraph(false, model);
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}

void NextReactionMethodCompact::reacTimeGeneration()
{
    //generates the absolute time for each reaction and saves it in the priority queue
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i);
        u = ut->getRandomNumber();
        delta[i] = (-1.00) * ut->ln(u);
        if (propArray[i] > EP)
            t1 = (delta[i] / propArray[i]) + currentTime;
        else
            t1 = INF;
        propNonZero[i] = propArray[i]; //if propArray[i] = propNonZero[i] = 0, that happens since the beginning of the simulation
        queue->insertKey(i, t1);
    }
    //queue->sort();
}
void NextReactionMethodCompact::reacSelection()
{
    //selects the node with the minimal time and updates the time
    cOld = currentTime;
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();
    if (cOld >= currentTime)
        cout << "WRONG-> " << cOld << " " << currentTime << endl;
}
void NextReactionMethodCompact::reacExecution()
{
    double u;  //random number
    double nt; //new time
    double propOld;
    int index;
    int sIndex = selectedNode->getIndex();
    updateSpeciesQuantities(sIndex);
    calcPropOne(sIndex);
    propNonZero[sIndex] = propArray[sIndex];
    u = ut->getRandomNumber();
    delta[sIndex] = -1 * ut->ln(u);
    if (propArray[sIndex] > 0)
    {
        nt = (delta[sIndex] / propArray[sIndex]) + currentTime;
    }
    else
    {
        nt = INF;
    }
    queue->update(sIndex, nt);
    //uses the DG to update the time of the selected reaction on the priority Queue
    int *depArray = dg->getDependencies(sIndex);
    int depSize = dg->getDependenciesSize(sIndex);
    for (int i = 0; i < depSize; i++)
    {
        index = depArray[i];
        propOld = propArray[index];
        calcPropOne(index);
        nt = INF;
        if (propArray[index] > EP)
        {
            nt = (delta[index] - (propNonZero[index] * currentTime)) / propArray[index] + currentTime;
            propNonZero[index] = propArray[index];
            delta[index] = propArray[index] * nt;
        }
        else if (propOld > EP)
        {
            propNonZero[index] = (-1.0 * propOld);
            delta[index] = propOld * currentTime;
        }
        //if both propensities(last and current) are 0 so nt = INF
        queue->update(index, nt);
    }
    delete[] depArray;
}
void NextReactionMethodCompact::perform(Model *model, double maximumTime, double initialTime, long int seed)
{
    cout << "-----------NEXT REACTION METHOD COMPACT-----------" << endl;
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
    log->insertNode(currentTime, specQuantity); //saves the species quantities on initialTime
    reacSelection();
    if (currentTime != INF)
    {
        while (currentTime < maximumTime)
        {
            reacExecution();
            log->insertNode(currentTime, specQuantity);
            reacSelection();
        }
    }
    cout << cOld << endl;
    double en = ut->getCurrentTime(); //ending of the simulation
    sucess = true;
    reacPerSecond = (double)reacCount / (en - beg);
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    cout << "Reactions per second: " << reacPerSecond << endl;
    log->setReacPerSecond(reacPerSecond);
    log->setNumberReacExecuted(reacCount);
}
NextReactionMethodCompact::~NextReactionMethodCompact()
{
    delete[] delta;
    delete queue;
    delete selectedNode;
}
