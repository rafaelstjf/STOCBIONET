#include "FirstReactionMethod.hpp"

FirstReactionMethod::~FirstReactionMethod()
{
    //dtor
}
void FirstReactionMethod::initialize(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    model->loadModel(filename);
    specQuantity = new int[model->getSpecNumber()];
    propArray = new double[model->getReacNumber()];
    this->simulTime = simulTime;
    totalPropensity = 0;
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = model->getInitialQuantity()[i];
    }
    t = new double[model->getReacNumber()];
}
void FirstReactionMethod::perform(string filename, double simulTime)
{
    cout << "FIRST REACTION METHOD" << endl;
    initialize(filename, simulTime);
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
        for (int i = 0; i < model->getReacNumber(); i++)
        {
            calcPropOne(i);
            u = ut->getRandomNumber();
            t[i] = (-1.0) * log10(u) / propArray[i];
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
void FirstReactionMethod::calcPropensity()
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
void FirstReactionMethod::calcPropOne(int index)
{
    int sum = 1;
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
}
void FirstReactionMethod::saveToFile()
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
    ut->saveToCSV(buffer.str(), "FRM_output");
}
void FirstReactionMethod::printResult()
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
