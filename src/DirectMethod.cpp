#include "../include/DirectMethod.hpp"
void DirectMethod::initialization(string filename, double simultime)
{
    //instantiates the variables
    model = new Model(); //instantiates the model
    ut = new Utils();    //instantiates the utility class
    model->loadModel(filename);
    t = 0.0; //tal
    selectedReaction = 0;
    this->simulTime = simulTime;
    totalPropensity = 0;
    sucess = false;
    reacCount = 0;
    reacPerSecond = 0.0;
    //creates the output file's name
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
    //loads both log and the depedency graph
    if (model->isModelLoaded())
    {
        log = new Log(model->getSpecNumber());
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void DirectMethod::reacTimeGeneration()
{
    double u1;
    u1 = ut->getRandomNumber();
    t = (-1.0* ut->ln(u1))/ totalPropensity;//next time increases
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
    updateSpeciesQuantities(selectedReaction);
    //check the dependencies of the selected reaction and update the propensity array
    int *depArray = dg->getDependencies(selectedReaction);
    int depSize = dg->getDependenciesSize(selectedReaction);
    for (int i = 0; i < depSize; i++)
    {
        calcPropOne(depArray[i]);
    }
    delete [] depArray;
    currentTime = currentTime + t;
}
void DirectMethod::perform(string filename, double simulTime, double beginTime)
{
    cout << "DIRECT METHOD" << endl;
    initialization(filename, simulTime); //instantiates the variables
    //checks if the model is loaded
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime(); //beginning of the simulation
    currentTime = beginTime;
    t = 0.0;
    //peforms the simulation
    calcPropensity();    //calculate the reactions propensity
    while (currentTime <= simulTime)
    {
        //saves the current species quantities on the log 
       log->insertNode(currentTime, specQuantity);
        //generates simulation time
        reacTimeGeneration();
        //reaction's selection
        reacSelection();
        //reaction's execution
        reacExecution();
    }
    double en = ut->getCurrentTime(); //ending of the simulation
    sucess = true;
    reacPerSecond = (double)reacCount/(en-beg);
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    cout << "Reactions per second: " << reacPerSecond << endl;
    log->setReacPerSecond(reacPerSecond);
    log->setNumberReacExecuted(reacCount);
    saveToFile();
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
    
}
