#include "RejectionMethod.hpp"

void RejectionMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{

    SSA::initialization(model, maximumTime, initialTime, seed);
    methodOutName += "_RM_output";
    if (model->isModelLoaded())
    {
        delayStructure = new DelayHash(model->getSpecNumber(), initialTime, maximumTime, 0.000001);
        dg = new DependencyGraph(true, model);
        ddg = new DelayedDependencyGraph(model);
    }
}
void RejectionMethod::reacSelection()
{

    double u = ut->getRandomNumber();
    double selector;
    if (totalPropensity <= EP)
        selectedReaction = -1;
    else
    {
        selector = totalPropensity * u;
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
    //cout << "Selected reaction: " << selectedReaction << endl;
}
void RejectionMethod::reacTimeGeneration()
{
}
void RejectionMethod::updateSpeciesQuantities(int index)
{
    reacCount++;
    //updates the reactants and add the product on the delay list if it has delay
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        if (model->getDelaysValue()[i][index] > EP)
        {
            delayStructure->insertKey(i, index, (currentTime + model->getDelaysValue()[i][index]));
            specQuantity[i] = specQuantity[i] - model->getReactants()[i][index];
        }
        else
            specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[i][index];
    }
}
void RejectionMethod::reacExecution()
{
    double tal = 0.0;
    double u = ut->getRandomNumber();
    double teta = (-1 * ut->ln(u)) / totalPropensity;
    double sum = 0;
    DelayNode *first = delayStructure->getMinNode();
    if (first != nullptr && first->getDelayTime() > currentTime && first->getDelayTime() <= (currentTime + teta))
    {
        tal = first->getDelayTime();
        vector<DelayNode *> elements = delayStructure->extractEqual(tal);
        for (int i = 0; i < elements.size(); i++)
        {
            int reacIndex = elements[i]->getReacIndex();
            int specIndex = elements[i]->getSpecIndex();
            double delayTime = elements[i]->getDelayTime();
            //updates the specie quantity for each product in delay
            specQuantity[specIndex] = specQuantity[specIndex] + model->getProducts()[specIndex][reacIndex];
            //updates the propensity for all the reactions that this one affects
            int *depArray = ddg->getDependencies(specIndex);
            int depSize = ddg->getDependenciesSize(specIndex);
            for (int j = 0; j < depSize; j++)
            {
                calcPropOne(depArray[j]);
            }
            delete depArray;
        }
        currentTime = tal;
        for (int i = 0; i < elements.size(); i++)
        {
            delete elements[i];
        }
    }
    else
    {
        reacSelection();
        if (selectedReaction == -1)
        {
            currentTime = INF;
        }
        else
        {

            updateSpeciesQuantities(selectedReaction);
            currentTime = currentTime + teta;

            //calcPropensity();
            int *depArray = dg->getDependencies(selectedReaction);
            int depSize = dg->getDependenciesSize(selectedReaction);
            for (int j = 0; j < depSize; j++)
            {
                calcPropOne(depArray[j]);
            }
            delete depArray;
        }
    }
}
void RejectionMethod::perform(Model *model, double maximumTime, double initialTime, long int seed)
{
    cout << "-----------REJECTION METHOD-----------" << endl;
    initialization(model, maximumTime, initialTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = initialTime;
    calcPropensity();
    while (currentTime < maximumTime)
    {
        log->insertNode(currentTime, specQuantity);
        reacExecution();
        delayStructure->print();
    }
    double en = ut->getCurrentTime(); //ending of the simulation
    sucess = true;
    reacPerSecond = (double)reacCount / (en - beg);
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    cout << "Reactions per second: " << reacPerSecond << endl;
    log->setReacPerSecond(reacPerSecond);
    log->setNumberReacExecuted(reacCount);
}
RejectionMethod::~RejectionMethod()
{
    delete delayStructure;
}