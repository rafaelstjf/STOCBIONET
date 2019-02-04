#include "../include/SortingDirectMethod.hpp"

void SortingDirectMethod::initialization(Model *model, double simulTime, long int seed)
{
    //instantiates the variables
    this->model = model;
    string filename = model->getFilename();
    if (seed >= 0) //instantiates the utility class
        ut = new Utils(seed);
    else
        ut = new Utils();
    this->simulTime = simulTime;
    totalPropensity = 0.0;
    sucess = false;
    reacCount = 0;
    reacPerSecond = 0.0;
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_SDM_output";
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
        reactionSO = new int[model->getReacNumber()]; //creates an array to sort the most used reactions
        dg = new DependencyGraph(true, model);
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
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
void SortingDirectMethod::perform(Model *model, double simulTime, double beginTime, long int seed)
{
    cout << "-----------SORTING DIRECT METHOD-----------" << endl;
    initialization(model, simulTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = beginTime;
    //peforms the simulation
    calcPropensity(); //calculate the reactions propensity
    while (currentTime < simulTime)
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
    delete [] reactionSO;
}