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
    ut->saveToCSV(buffer.str(), methodOutName);
}