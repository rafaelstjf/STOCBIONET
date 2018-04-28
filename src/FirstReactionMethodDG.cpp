#include "../include/FirstReactionMethodDG.hpp"

FirstReactionMethodDG::~FirstReactionMethodDG()
{
    //dtor
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
    delete[] t;
}
void FirstReactionMethodDG::initialization(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    model->loadModel(filename);
    this->simulTime = simulTime;
    if(model->isModelLoaded())
    {
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
        t = new double[model->getReacNumber()];
    }

}
void FirstReactionMethodDG::perform(string filename, double simulTime)
{
    cout << "FIRST REACTION METHOD USING DEPENDENCY GRAPH" << endl;
    initialization(filename, simulTime);
    if(!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return ;
    }
    double beg = ut->getCurrentTime();
    double currentTime = 0.0;
    double selector = 0.0;
    double u = 0.0;
    int *xArray;
    int selectedReaction = 0;
    x.clear();
    calcPropensity();
    while (currentTime <= simulTime)
    {
        xArray = new int[model->getSpecNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            xArray[i] = specQuantity[i];
        }
        x.insert(make_pair(currentTime, xArray));
        //reaction selection
        if (currentTime == 0)
        {
            //first execution
            for (int i = 0; i < model->getReacNumber(); i++)
            {
                calcPropOne(i);
                u = ut->getRandomNumber();
                t[i] = (-1.0) * log10(u) / propArray[i];
            }
        }
        else
        {
            //after the first iteration, updates the tau only in the affected reactions using the DG
            int *depArray = dg->getDependencies(selectedReaction);
            int depSize = dg->getDependenciesSize(selectedReaction);
            for (int i = 0; i < depSize; i++)
            {
                calcPropOne(depArray[i]);
                u = ut->getRandomNumber();
                t[depArray[i]] = (-1.0) * log10(u) / propArray[depArray[i]];
            }
        }
        double minT = t[0];
        selectedReaction = 0;
        for (int i = 1; i < model->getReacNumber(); i++)
        {
            if (minT > t[i])
            {
                minT = t[i];
                selectedReaction = i;
            }
        }
        currentTime = currentTime + minT;
        //reaction execution
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[selectedReaction][i];
        }
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    //printResult();
    saveToFile();
}
void FirstReactionMethodDG::calcPropensity()
{
    int sum = 1;
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
void FirstReactionMethodDG::calcPropOne(int index)
{
    int sum = 1;
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
}
void FirstReactionMethodDG::saveToFile()
{
    stringstream buffer;
    map<string, long int> speciesNameNumber = model->getSpecNameNumber();
    map<double, int *>::iterator itX = x.begin();
    map<string, long int>::iterator itSpecies = speciesNameNumber.begin();
    //get the name of the species
    string names[speciesNameNumber.size()];
    while (itSpecies != speciesNameNumber.end())
    {
        names[itSpecies->second] = itSpecies->first;
        itSpecies++;
    }
    buffer.clear();
    buffer << "Time; ";
    for (int i = 0; i < speciesNameNumber.size(); i++)
    {
        buffer << names[i];
        if (i < speciesNameNumber.size() - 1)
            buffer << "; ";
    }
    buffer << '\n';
    while (itX != x.end())
    {
        int *a = itX->second;
        buffer << itX->first << "; ";
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            buffer << a[i];
            if (i < model->getSpecNumber() - 1)
                buffer << "; ";
        }
        buffer << '\n';
        itX++;
    }
    ut->saveToCSV(buffer.str(), "FRMDG_output");
}
void FirstReactionMethodDG::printResult()
{
    map<double, int *>::iterator it = x.begin();
    while (it != x.end())
    {
        int *a = it->second;
        cout << "Time: " << it->first << endl;
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            cout << a[i];
            if (i < model->getSpecNumber() - 1)
                cout << ": ";
        }
        cout << endl;
        it++;
    }
}
