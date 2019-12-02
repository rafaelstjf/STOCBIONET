#include "OptimizedDirectMethod.hpp"

void OptimizedDirectMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    SSA::initialization(model, maximumTime, initialTime, seed);
    methodOutName += "_ODM_output";
    if (model->isModelLoaded())
    {
        reactionSO = new int[model->getReacNumber()];
        dg = model->getDG();
        for (int i = 0; i < model->getReacNumber(); i++)
        {
            reactionSO[i] = 0;
        }
    }
}
void OptimizedDirectMethod::reacTimeGeneration()
{
    double u1;
    u1 = ut->getRandomNumber();
    t = (-1.0 * ut->ln(u1)) / totalPropensity;
}
void OptimizedDirectMethod::reacSelection()
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
void OptimizedDirectMethod::reacExecution()
{
    if (selectedReaction == -1)
    {
        currentTime = INF;
        return;
    }
    updateSpeciesQuantities(selectedReaction);
    int *depArray = dg->getDependencies(selectedReaction);
    int depSize = dg->getDependenciesSize(selectedReaction);
    for (int i = 0; i < depSize; i++)
    {
        calcPropOne(depArray[i]);
    }
    delete[] depArray;
    currentTime = currentTime + t;
}

void OptimizedDirectMethod::preSimul()
{
    double maxTime = (maximumTime*1.0) / 3;
    double cTime = initialTime;
    this->pSimul = true;
    calcPropensity();
    while (cTime < maxTime)
    {
        reacTimeGeneration();
        //reaction's selection
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
                    reactionSO[i]++; //increases the number of times that this reaction was selected
                    break;
                }
            }
        }
        //reaction's execution
        if (selectedReaction == -1)
        {
            cTime = INF;
        }
        else
        {
            updateSpeciesQuantities(selectedReaction);
            int *depArray = dg->getDependencies(selectedReaction);
            int depSize = dg->getDependenciesSize(selectedReaction);
            for (int i = 0; i < depSize; i++)
            {
                calcPropOne(depArray[i]);
            }
            delete[] depArray;
            cTime = cTime + t;
        }
    }
    //reset the species' quantity
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = model->getInitialQuantity()[i];
    }
    double *temp = new double[model->getReacNumber()];
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        temp[i] = i;
    }
    //sorting in decreasing order
    int j, key, k, key2;
    for (j = 1; j < model->getReacNumber(); j++)
    {
        key = reactionSO[j];
        key2 = temp[j];
        k = j - 1;
        while (k >= 0 && reactionSO[k] < key)
        {
            reactionSO[k + 1] = reactionSO[k];
            temp[k + 1] = temp[k];
            k = k - 1;
        }
        reactionSO[k + 1] = key;
        temp[k + 1] = key2;
    }
    for (j = 0; j < model->getReacNumber(); j++)
    {
        
        reactionSO[j] = temp[j]; //now reactionSO has the index of the reactions in ordered decreasing order
    }
    reacCount = 0;
    delete[] temp;
}
void OptimizedDirectMethod::perform(Model *model, double maximumTime, double initialTime, long int seed)
{
    cout << "-----------OPTIMIZED DIRECT METHOD-----------" << endl;
    initialization(model, maximumTime, initialTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = initialTime;
    //performs the pre-simulation
    preSimul();
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
    postSimulation((en - beg));
}
OptimizedDirectMethod::~OptimizedDirectMethod()
{
    delete[] reactionSO;
}