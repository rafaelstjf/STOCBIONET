#include "../include/FirstReactionMethodDG.hpp"
void FirstReactionMethodDG::initialization(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    model->loadModel(filename);
    methodOutName = "FRMDG_output";
    this->simulTime = simulTime;
    if (model->isModelLoaded())
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
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = 0.0;
    int *xArray;
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
        //generate simulation time
        reacTimeGeneration();
        //reaction selection
        reacSelection();
        //reaction execution
        reacExecution();
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    //printResult();
    saveToFile();
}
void FirstReactionMethodDG::reacSelection()
{
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
}
void FirstReactionMethodDG::reacTimeGeneration()
{
    double u = 0.0;
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
}
FirstReactionMethodDG::~FirstReactionMethodDG()
{
    //dtor
}