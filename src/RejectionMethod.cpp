#include "../include/RejectionMethod.hpp"

void RejectionMethod::initialization(string filename, double simultime, long int seed)
{
    model = new Model();
    if (seed >= 0)
        ut = new Utils(seed);
    else
        ut = new Utils();
    model->loadModel(filename);
    this->simulTime - simultime;
    sucess = false;
    reacCount = 0;
    reacPerSecond = 0.0;
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] = '.')
        {
            methodOutName += "_RM_output";
            break;
        }
        else
            methodOutName += filename[i];
    }
    if (model->isModelLoaded())
    {
        log = new Log(model->getSpecNumber());
        list = new DelayList();
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void RejectionMethod::reacSelection()
{
    double u = ut->getRandomNumber();
    double selector;
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
void RejectionMethod::reacTimeGeneration()
{
}
void RejectionMethod::updateSpeciesQuantities(int index)
{
    //updates the reactants and add the product on the delay list if it has delay
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        if (model->getDelaysValue()[i][index] > EP)
            list->insert(i, index, (currentTime + model->getDelaysValue()[i][index]));
        else
            specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[i][index];
    }
}
void RejectionMethod::reacExecution()
{
    double tal;
    double u = ut->getRandomNumber();
    double teta = (-1 * ut->ln(u)) / totalPropensity;
    if (list->getArraySize() > 0 && (list->getDelayTime(0) > currentTime && list->getDelayTime(0) <= currentTime + teta))
    {
        tal = list->getDelayTime(0);
        for (int i = 0; i < list->getArraySize(); i++)
        {
            int specIndex = list->getSpecIndex(i);
            int reacIndex = list->getReacIndex(i);
            double delayTime = list->getDelayTime(i);
            if (delayTime == tal)
            {
                //updates the specie quantity for each product in delay
                specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[specIndex][reacIndex];
                //updates the propensity for all the reactions that this one affects
                int *depArray = dg->getDependencies(reacIndex);
                int depSize = dg->getDependenciesSize(reacIndex);
                for (int j = 0; j < depSize; j++)
                {
                    calcPropOne(depArray[j]);
                }
                delete depArray;
                list->removeByArrayIndex(i);
                i--; //reduces the iterator because of the removal
            }
        }
        currentTime = tal;
    }
    else
    {
        reacSelection();
        updateSpeciesQuantities(selectedReaction);
        currentTime = currentTime + teta;
        int *depArray = dg->getDependencies(selectedReaction);
        int depSize = dg->getDependenciesSize(selectedReaction);
        for (int j = 0; j < depSize; j++)
        {
            calcPropOne(depArray[j]);
        }
        delete depArray;
    }
}
void RejectionMethod::perform(string filename, double simulTime, double beginTime, long int seed)
{
    cout << "-----------REJECTION METHOD-----------" << endl;
    initialization(filename, simulTime, seed); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = beginTime;
    calcPropensity();
    while (currentTime < simulTime)
    {
        log->insertNode(currentTime, specQuantity);
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
RejectionMethod::~RejectionMethod()
{
    delete list;
}