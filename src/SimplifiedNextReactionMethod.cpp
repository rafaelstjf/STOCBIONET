#include "../include/SimplifiedNextReactionMethod.hpp"

void SimplifiedNextReactionMethod::initialization(string filename, double simulTime)
{
    sucess = false;
    model = new Model();
    ut = new Utils();
    this->simulTime = simulTime;
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_SNRM_output";
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
void SimplifiedNextReactionMethod::reacTimeGeneration()
{
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i);
        u = ut->getRandomNumber();
        P[i] = (-1.0*ut->ln(u));
        U[i] = currentTime;
        T[i] = 0.0;
        t1 = (P[i] - T[i])/propArray[i] + currentTime;
        queue->insertKey(i, t1);
    }
}
void SimplifiedNextReactionMethod::reacSelection()
{
    //selects the node with the minimal time and updates the time
    selectedNode = queue->getMin();
    currentTime = selectedNode->getTime();

}
void SimplifiedNextReactionMethod::reacExecution()
{
    double u; //random number
    double nt; //new time
    int index;
    int sIndex = selectedNode->getIndex();
    //updates the species quantities
    for(int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[sIndex][i];
    }
    u = ut->getRandomNumber();
    P[sIndex] = P[sIndex] + (-1.0*ut->ln(u));
    int *depArray = dg->getDependencies(sIndex);
    int depSize = dg->getDependenciesSize(sIndex);
    for (int i = 0; i < depSize; i++)
    {
        index = depArray[i];
        T[index] = T[index] + propArray[index]*(currentTime - U[index]);
        U[index] = currentTime;
        calcPropOne(index);
        nt = (P[index] - T[index])/propArray[index] + currentTime;
        queue->update(index, nt);
    }

}
void SimplifiedNextReactionMethod::perform(string filename, double simulTime, double beginTime)
{
    cout << "SIMPLIFIED NEXT REACTION METHOD" << endl;
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
    //calculates the propensity of all the reactions and generates the simulation time
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
            reacSelection(); //selects a reaction 
            reacExecution();//executes the selected reaction
        }
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    sucess = true;
    saveToFile();
}
SimplifiedNextReactionMethod::~SimplifiedNextReactionMethod()
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
