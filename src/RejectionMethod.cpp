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
        list = new List(model->getReacNumber());
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
}
void RejectionMethod::reacTimeGeneration()
{
}
void RejectionMethod::reacExecution()
{
    double tal;
    double u = ut->getRandomNumber();
    double teta = (-1 * ut->ln(u)) / totalPropensity;
    selectedNode = list->getMin();
    if (selectedNode != nullptr && (selectedNode->getTime() > currentTime && selectedNode->getTime() <= currentTime + teta))
    {
        tal = selectedNode->getTime();
        int size = list->getSize();
        for (int i = 0; i < size; i++)
        {
            HeapNode *currentNode = list->getOnPosition(i);
            if (currentNode->getTime() == tal)
            {
                list->removeIndex(i);
                int *depArray = dg->getDependencies(currentNode->getIndex());
                int depSize = dg->getDependenciesSize(currentNode->getIndex());
                for (int j = 0; j < model->getSpecNumber(); j++)
                {
                    int coef = model->getStoiMatrix()[j][currentNode->getIndex()];
                    if(coef > 0)
                        specQuantity[j] = specQuantity[j] + model->getStoiMatrix()[j][currentNode->getIndex()];
                }
                for (int j = 0; j < depSize; j++)
                {
                    calcPropOne(depArray[i]);
                }
                delete depArray;
            }
        }
        currentTime = tal;
    }
    else
    {
        u = ut->getRandomNumber();
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
        reacExecution();
        log->insertNode(currentTime, specQuantity);
    }
    log->insertNode(currentTime, specQuantity);
}
RejectionMethod::~RejectionMethod()
{
    delete list;
}