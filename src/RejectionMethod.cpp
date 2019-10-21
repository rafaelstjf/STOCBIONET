#include "RejectionMethod.hpp"

void RejectionMethod::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{

    SSA::initialization(model, maximumTime, initialTime, seed);
    methodOutName += "_RM_output";
    if (model->isModelLoaded())
    {
        chooseStructure();
        dg = model->getDGSelfEdge();
        ddg = model->getDDG();
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
    DelayNode *first = delayStructure->getMinNode();
    if (first != nullptr && first->getDelayTime() >= currentTime && first->getDelayTime() <= (currentTime + teta))
    {
        tal = first->getDelayTime();
        vector<DelayNode *> elements = delayStructure->extractEqualFirst();
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            int reacIndex = elements[i]->getReacIndex();
            int specIndex = elements[i]->getSpecIndex();
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
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            delete elements[i];
        }
        elements.clear();
        currentTime = tal;
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

            currentTime = currentTime + teta;
            updateSpeciesQuantities(selectedReaction);

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
    }
    double en = ut->getCurrentTime(); //ending of the simulation
    postSimulation((en - beg));
}
void RejectionMethod::chooseStructure()
{
    switch (structOp)
    {
    case 1:

        cout << "1 - List" << endl;
        delayStructure = new DelayList();
        break;
    case 2:
        cout << "2 - Heap" << endl;
        delayStructure = new DelayHeap(model->getReacNumber());
        break;
    case 3:
        cout << "3 - Circular List" << endl;
        delayStructure = new CircularList(model->getReacNumber());
        break;
    case 4:
        cout << "4 - Hash Table" << endl;
        delayStructure = new DelayHash(model->getDelaysValue(), model->getReacNumber(), model->getSpecNumber());
        break;
    }
}
void RejectionMethod::setDelayStructure(int op)
{
    structOp = op;
}
RejectionMethod::~RejectionMethod()
{
    delete delayStructure;
}