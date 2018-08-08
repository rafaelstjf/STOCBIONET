#include "../include/SSA.hpp"
SSA::~SSA()
{
    delete dg;
    delete model;
    delete ut;
    delete log;
    delete[] specQuantity;
    delete[] propArray;
}
Log *SSA::getLog()
{
    return log;
}
void SSA::saveToFile()
{
    string date = ut->getCurrentDateTime();
    string logName = "logs/" + ut->extractFileName(methodOutName) + "_" + date;
    stringstream buffer;
    map<string, long int> speciesNameNumber = model->getSpecNameNumber();
    map<string, long int>::iterator itSpecies = speciesNameNumber.begin();
    //get the name of the species
    string names[speciesNameNumber.size()];
    cout << "SAVING SIMULATION RESULTS IN " << methodOutName << "_" << ut->getCurrentDateTime() << endl;
    cout << "SAVING SIMULATION LOG IN " << logName << endl;
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
    buffer << log->exportToStringStream().str();
    speciesNameNumber.clear();
    ut->saveToCSVNoOverwriting(buffer.str(), methodOutName + "_" + date);
    stringstream buffer2;
    buffer2 << "Number of reactions executed: " << log->getNumberReacExecuted() << '\n';
    buffer2 << "Reactions per second: " << log->getReacPerSecond() << '\n';
    buffer2 << "Seed: " << ut->getSeed() << '\n';
    ut->saveToTXT(buffer2.str(), logName);
    buffer.clear();
    buffer2.clear();
}
void SSA::printResult()
{
    log->printLog();
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
void SSA::updateSpeciesQuantities(int index)
{
    reacCount++;
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[index][i];
    }
}
bool SSA::checkSucess()
{
    return sucess;
}
