#include "SSA.hpp"
SSA::~SSA()
{
    delete ut;
    delete log;
    delete[] specQuantity;
    delete[] propArray;
}
Log *SSA::getLog()
{
    return log;
}
void SSA::initialization(Model *model, double maximumTime, double initialTime, long int seed)
{
    //instantiates the variables
    this->model = model;
    this->maximumTime = maximumTime;
    this->initialTime = initialTime;
    this->sucess = false;
    this->reacCount = 0;
    this->reacPerSecond = 0;
    //creates the output file's name
    methodOutName = ut->removeFilePath(model->getFilename());
    methodOutName = ut->removeFileType(methodOutName);
    if (seed >= 0)
        this->ut = new Utils(seed); //instantiates the utility class with a custom seed
    else
        this->ut = new Utils(); //instantiates the utility class with a generated seed
    if (model->isModelLoaded())
    {
        this->log = new Log(model->getSpecNumber(), model->getSpecNameNumber());
        this->specQuantity = new double[model->getSpecNumber()];
        this->propArray = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
            this->specQuantity[i] = model->getInitialQuantity()[i];
    }
}
void SSA::saveToFile()
{
    string date = ut->getCurrentDateTime();
    string logName = "log_" + methodOutName + "_" + date;
    string resultName = methodOutName + "_" + date;
    log->saveResultsToFile(resultName);
    //saving log
    log->saveDetailsToFile(logName, ut->getSeed());
}
void SSA::saveDetailsToFile()
{
    string date = ut->getCurrentDateTime();
    string logName = "log_" + methodOutName + "_" + date;
    log->saveDetailsToFile(logName, ut->getSeed());
}
void SSA::printResult()
{
    log->printLog();
}
unsigned long int SSA::getSeed()
{
    return ut->getSeed();
}
double SSA::getReacPerSecond()
{
    return log->getReacPerSecond();
}
double SSA::getNumberReacExecuted()
{
    return log->getNumberReacExecuted();
}
void SSA::onBatch(){
    batch = true;
}
void SSA::calcPropensity()
{
    totalPropensity = 0.0;
    double sum;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 1;
        for (int j = 0; j < model->getSpecNumber(); j++)
        {
            sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[j][i]);
        }
        propArray[i] = model->getReacRateArray()[i] * sum;
        totalPropensity += propArray[i];
    }
}
void SSA::calcPropOne(int index)
{
    double sum = 1;
    double propOld = propArray[index];
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[j][index]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
    totalPropensity = totalPropensity - propOld + propArray[index];
}
void SSA::updateSpeciesQuantities(int index)
{
    reacCount++;
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[i][index];
    }
}
bool SSA::checkSucess()
{
    return sucess;
}
void SSA::postSimulation(double totalTime)
{
    sucess = true;
    reacPerSecond = (double)reacCount / (totalTime);
    if(!batch){
        cout << "\nSimulation finished with " << totalTime << " seconds." << endl;
        cout << "Reactions per second: " << reacPerSecond << endl;
    }
    log->setReacPerSecond(reacPerSecond);
    log->setNumberReacExecuted(reacCount);
    log->setTimeSpent(totalTime);
}
double SSA::getTimeSpent()
{
    return log->getTimeSpent();
}
