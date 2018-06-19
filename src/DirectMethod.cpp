#include "../include/DirectMethod.hpp"
void DirectMethod::initialization(string filename, double simultime)
{
    //instantiate the variables
    model = new Model(); //instantiate the model
    ut = new Utils();    //instantiate the utility class
    model->loadModel(filename);
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_DM_output";
            break;
        }

        else
            methodOutName += filename[i];
    }
    t = 0.0; //tal
    selectedReaction = 0;
    this->simulTime = simulTime;
    totalPropensity = 0;
    //load both model and its depedency graph
    if (model->isModelLoaded())
    {
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        //dg->printGraph();
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
    sucess = false;
}
void DirectMethod::reacTimeGeneration()
{
    double u1;
    u1 = ut->getRandomNumber();
    t = (-1.0* ut->ln(u1))/ totalPropensity;//next time increase
}
void DirectMethod::reacSelection()
{
    double selector;
    double u2;
    u2 = ut->getRandomNumber();
    selector = totalPropensity * u2;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        selector = selector - propArray[i];
        if (selector <= 0.0)
        {
            selectedReaction = i;
            break;
        }
    }
}
void DirectMethod::reacExecution()
{
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[selectedReaction][i];
    }
    //check the dependencies of the selected reaction and update the propensity array
    int *deparray = dg->getDependencies(selectedReaction);
    int depSize = dg->getDependenciesSize(selectedReaction);
    for (int i = 0; i < depSize; i++)
    {
        calcPropOne(deparray[i]);
    }
}
void DirectMethod::perform(string filename, double simulTime, double beginTime)
{
    cout << "DIRECT METHOD" << endl;
    initialization(filename, simulTime); //instantiate the variables
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //begin
    //peform the simulation
    currentTime = beginTime;
    t = 0.0;
    int *xArray;
    x.clear();
    //calculate the reactions propensity
    calcPropensity();
    while (currentTime <= simulTime)
    {
        //save the current species quantities on the map
        xArray = new int[model->getSpecNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            // xArray[i] = 0;
            xArray[i] = specQuantity[i];
        }
        x.insert(make_pair(currentTime, xArray));
        //generate simulation time
        reacTimeGeneration();
        //reaction selection
        reacSelection();
        //reaction execution
        reacExecution();
        currentTime = currentTime + t;
    }
    double en = ut->getCurrentTime(); //end
    saveToFile();
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    sucess = true;
}
void DirectMethod::calcPropensity()
{
    //updates the entire array of propensities
    //propensity of a reaction i is: reaction rate * productory(n=0; n=numSpecies) of binomialcoefficient(SpecQuantity[n],reactants[i][n]

    double sum;
    int **reactants = model->getReactants();
    double *rate = model->getReacRateArray();
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 1;
        for (int j = 0; j < model->getSpecNumber(); j++)
        {
            sum *= ut->binomialCoefficient(specQuantity[j], reactants[i][j]);
        }
        propArray[i] = rate[i] * sum;
        totalPropensity += propArray[i];
    }
}
void DirectMethod::calcPropOne(int index)
{
    //updates the propensity of the selected reaction
    double sum = 1;
    double propOld = propArray[index];
    int *reactants = model->getReactants()[index];
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        sum *= ut->binomialCoefficient(specQuantity[i], reactants[i]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
    totalPropensity = totalPropensity - propOld + propArray[index];
}
DirectMethod::~DirectMethod()
{
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
}
