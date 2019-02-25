#include "ModifiedNextReactionMethod.hpp"

void ModifiedNextReactionMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    //instantiates the variables
    sucess = false;
    this->model = model;
    this->maximumTime = maximumTime;
    this->initialTime = initialTime;
    if (seed >= 0)
        ut = new Utils(seed); //instantiates the utility class
    else
        ut = new Utils(); //instantiates the utility class    this->maximumTime = maximumTime;
    reacCount = 0;
    reacPerSecond = 0.0;
    //creates the output file's name
    methodOutName = (ut->extractFileName(model->getFilename() + "_MNRM_output"));
    //loads both log and the depedency graph
    if (model->isModelLoaded())
    {
        log = new Log(model->getSpecNumber());
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        dg = new DependencyGraph(true, model);
        P = new double[model->getReacNumber()];
        T = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
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
    u = ut->getRandomNumber();
    P[sIndex] = P[sIndex] + (-1.0 * ut->ln(u));
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        T[i] = T[i] + propArray[i] * selectedNode->getTime();
    }
    int *depArray = dg->getDependencies(sIndex);
    int depSize = dg->getDependenciesSize(sIndex);
    for (int i = 0; i < depSize; i++)
    {
        calcPropOne(depArray[i]);
    }
    delete[] depArray;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        nt = (P[i] - T[i]) / propArray[i];
        queue->update(i, nt);
    }
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
    reacSelection();
    if (currentTime != inf)
    {
        currentTime = initialTime;
        while (currentTime < maximumTime)
        {
            log->insertNode(currentTime, specQuantity);
            reacSelection();
            reacExecution();
        }
    }
    double en = ut->getCurrentTime(); //ending of the simulation
    sucess = true;
    reacPerSecond = (double)reacCount / (en - beg);
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    cout << "Reactions per second: " << reacPerSecond << endl;
    log->setReacPerSecond(reacPerSecond);
    log->setNumberReacExecuted(reacCount);
}
ModifiedNextReactionMethod::~ModifiedNextReactionMethod()
{
    delete[] T;
    delete[] P;
    delete queue;
    delete dg;
    delete selectedNode;
}
