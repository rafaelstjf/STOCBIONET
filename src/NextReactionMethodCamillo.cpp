#include "../include/NextReactionMethodCamillo.hpp"

void NextReactionMethodCamillo::initialization(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    this->simulTime = simulTime;
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_NRMCAMILLO_output";
            break;
        }
        else
            methodOutName += filename[i];
    }
    model->loadModel(filename);
    if (model->isModelLoaded())
    {
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        //
        P = new double[model->getReacNumber()];
        U = new double[model->getReacNumber()];
        T = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void NextReactionMethodCamillo::calcPropensity()
{
    double sum;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 1;
        for (int j = 0; j < model->getSpecNumber(); j++)
        {
            sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[i][j]);
        }
        propArray[i] = model->getReacRateArray()[i] * sum;
    }
}
void NextReactionMethodCamillo::calcPropOne(int index)
{
    double sum = 1;
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
}
void NextReactionMethodCamillo::reacTimeGeneration()
{
    double u, t1, nt;
    for (int i = 0; i < model->getReacNumber(); i++)
    {

        u = ut->getRandomNumber();
        P[i] = (-1.0*ut->ln(u));
        U[i] = currentTime;
        T[i] = 0.0;
        nt = (P[i] - T[i])/propArray[i] + currentTime;
        queue->insertKey(i, t1);
    }
    //queue->sort();
}
void NextReactionMethodCamillo::reacSelection()
{
    //selects the node with the minimal time and updates the time
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();

}
void NextReactionMethodCamillo::reacExecution()
{
    double u; //random number
    double nt; //new time
    int index;
    int sIndex = selectedNode->getIndex();
    for(int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[sIndex][i];
    }
    calcPropOne(sIndex);
    P[sIndex] = P[sIndex] + (-1.0*ut->ln(u));
    int *depArray = dg->getDependencies(sIndex);
    int depSize = dg->getDependenciesSize(sIndex);
    for (int i = 0; i < depSize; i++)
    {
        index = depArray[i];
        T[index] = T[index] + propArray[index]*(currentTime - U[depArray[i]]);
        U[index] = currentTime;
        calcPropOne(depArray[i]);
        nt = (P[index] - T[index])/propArray[index] + currentTime;
        queue->update(index, nt);
    }

}
void NextReactionMethodCamillo::perform(string filename, double simulTime, double beginTime)
{
    cout << "NEXT REACTION METHOD COMPACT" << endl;
    initialization(filename, simulTime);
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = beginTime;
    int *xArray;
    x.clear();
    calcPropensity();
    //reacTimeGeneration comes before the while because you can calculate it only once and then
    //update inside the while
    reacTimeGeneration();
    //saves the species quantities on beginTime
    reacSelection();
    if(currentTime != inf)
    {
        currentTime = beginTime;
        //currentTime = beginTime;
        while (currentTime <= simulTime)
        {
            xArray = new int[model->getSpecNumber()];
            for (int i = 0; i < model->getSpecNumber(); i++)
            {
                xArray[i] = specQuantity[i];
            }
            x.insert(make_pair(currentTime, xArray));
            reacSelection();
            reacExecution();
        }
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    saveToFile();
}
NextReactionMethodCamillo::~NextReactionMethodCamillo()
{
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
    delete[] T;
    delete[] U;
    delete[] P;
    delete queue;
    delete selectedNode;
}
