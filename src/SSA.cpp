#include "../include/SSA.hpp"
SSA::~SSA()
{
}
void SSA::saveToFile()
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
    ut->saveToCSVNoOverwriting(buffer.str(), methodOutName);
}
void SSA::printResult()
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
void SSA::calcPropensity()
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
void SSA::calcPropOne(int index)
{
    double sum = 1;
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
}
bool SSA::checkSucess(){
    return sucess;
}
