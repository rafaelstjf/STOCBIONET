#include "../include/NextReactionMethodClassic.hpp"

void NextReactionMethodClassic::initialization(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    this->simulTime = simulTime;
    methodOutName = "NRMC_output";
    model->loadModel(filename);
    if(model->isModelLoaded())
    {
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        timePropZero = new double[model->getReacNumber()];
        propNonZero = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        dg = new DependencyGraphNRM(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        for(int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void NextReactionMethodClassic::calcPropensity()
{
    int sum;
    int** reactants = model->getReactants();
    double* rate = model->getReacRateArray();
    for(int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 1;
        for(int j = 0; j < model->getSpecNumber(); j++)
        {
            sum*=ut->binomialCoefficient(specQuantity[j], reactants[i][j]);

        }
        propArray[i] = rate[i]*sum;
    }
}
void NextReactionMethodClassic::calcPropOne(int index)
{
    int* reactants = model->getReactants()[index];
    int sum=1;
    for(int i = 0; i < model->getSpecNumber(); i++)
    {
        sum*=ut->binomialCoefficient(specQuantity[i], reactants[i]);
    }
    propArray[index] = model->getReacRateArray()[index]* sum;
}
void NextReactionMethodClassic::reacTimeGeneration()
{
    double u, t1;
    for(int i = 0; i < model->getReacNumber(); i++)
    {
        if(propArray[i]==0.0)
        {
            timePropZero[i] = currentTime;
            t1 = inf;
        }
        else
        {
            u = ut->getRandomNumber();
            t1 = ((-1*ut->ln(u))/propArray[i]) + currentTime;
        }
        propNonZero[i] = propArray[i];
        queue->insertKey(i, t1);
    }
}
void NextReactionMethodClassic::reacSelection()
{
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();
}
void NextReactionMethodClassic::reacExecution()
{
    double u;
    double nt;
    double propOld;
    double delta;
    int sIndex = selectedNode->getIndex();
    for(int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[sIndex][i];
    }
    calcPropOne(sIndex);
    if(propArray[sIndex] == 0.0)
    {
        timePropZero[sIndex] = currentTime;
        nt = inf;
    }
    else
    {
        u = ut->getRandomNumber();
        nt = ((-1*ut->ln(u))/propArray[sIndex]) + currentTime;
        propNonZero[sIndex] = propArray[sIndex];
    }
    queue->update(sIndex, nt);
    int* depArray = dg->getDependencies(sIndex);
    int depSize = dg->getDependenciesSize(sIndex);
    for(int i = 0; i < depSize; i++)
    {
        propOld = propArray[depArray[i]];
        calcPropOne(depArray[i]);
        if(propArray[depArray[i]] > 0.0)
        {
            if(propOld ==0.0)
            {
                if(propNonZero[depArray[i]] > 0.0)
                    delta = propNonZero[depArray[i]]*(currentTime - timePropZero[depArray[i]]);
                    //nt = (propNonZero[depArray[i]]/propArray[depArray[i]])*(currentTime-timePropZero[depArray[i]]) + currentTime;
                else
                {
                    u = ut->getRandomNumber();
                    //nt = ((-1*ut->ln(u))/propArray[depArray[i]]) + currentTime;
                    delta = (-1*ut->ln(u));
                }
            }
            else
                //nt = (propNonZero[depArray[i]]/propArray[depArray[i]])*(currentTime-timePropZero[depArray[i]]) + currentTime;
                delta = propNonZero[depArray[i]]*(selectedNode->getTime() - currentTime);
            nt = delta/propArray[depArray[i]] + currentTime;
            propNonZero[depArray[i]] = propArray[depArray[i]];
        }
        else if(propNonZero[depArray[i]] > 0.0)
        {
            timePropZero[depArray[i]] = currentTime;
            nt = inf;
        }
        queue->update(depArray[i], nt);
    }
}
void NextReactionMethodClassic::perform(string filename, double simulTime, double beginTime)
{
    cout << "NEXT REACTION METHOD CLASSIC" << endl;
    initialization(filename, simulTime);
    if(!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = beginTime;
    int *xArray;
    int oldCtime;
    x.clear();
    calcPropensity();
    reacTimeGeneration();
    reacSelection(); //just to check if the time = inf
    if(currentTime != inf)
    {
        currentTime = beginTime;
        while(currentTime <=simulTime)
        {
            xArray = new int[model->getSpecNumber()];
            for(int i = 0; i < model->getSpecNumber(); i++)
                xArray[i] = specQuantity[i];
            x.insert(make_pair(currentTime, xArray));
            reacSelection();
            reacExecution();
        }
    }
    double en = ut->getCurrentTime();
    cout << "\nSimulation finished with " << en-beg << " seconds." << endl;
    printResult();
    saveToFile();
}
NextReactionMethodClassic::~NextReactionMethodClassic()
{
    delete dg;
    delete model;
    delete ut;
    delete[] propNonZero;
    delete[] propArray;
    delete[] timePropZero;
    delete queue;
    delete selectedNode;
}
