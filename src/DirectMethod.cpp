#include "../include/DirectMethod.hpp"
void DirectMethod::initialization(Model *model, double simulTime, long int seed)
{
    //instantiates the variables
    this->model = model; //instantiates the model
    string filename = model->getFilename();
    if (seed >= 0)
        ut = new Utils(seed); //instantiates the utility class
    else
        ut = new Utils(); //instantiates the utility class
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
        dg = new DependencyGraph(true, model->getReactants(), model->getProducts(), model->getReacNumber(), model->getSpecNumber());
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
    t = (-1.0 * ut->ln(u1)) / totalPropensity; //next time increases
}
void DirectMethod::reacSelection()
{
    double selector;
    double u2;
    u2 = ut->getRandomNumber();
    if (totalPropensity <= EP)
        selectedReaction = -1;
    else
    {

        selector = totalPropensity * u2;
        for (int i = 0; i < model->getReacNumber(); i++)
        {
            selector = selector - propArray[i];
            if (selector <= EP)
            {
                selectedReaction = i;
                break;
            }
        }
    }
}
void DirectMethod::reacExecution()
{
    if (selectedReaction == -1)
    {
        currentTime = INF;
        return;
    }
    updateSpeciesQuantities(selectedReaction);
    //check the dependencies of the selected reaction and update the propensity array
    int *depArray = dg->getDependencies(selectedReaction);
    int depSize = dg->getDependenciesSize(selectedReaction);
    for (int i = 0; i < depSize; i++)
    {
        calcPropOne(depArray[i]);
    }
    delete[] depArray;
    currentTime = currentTime + t;
}
void DirectMethod::perform(Model* model, double simulTime, double beginTime, long int seed)
{
    cout << "-----------DIRECT METHOD-----------" << endl;
    initialization(model, simulTime, seed); //instantiates the variables
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
    calcPropensity(); //calculate the reactions propensity
    while (currentTime < simulTime)
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
    reacPerSecond = (double)reacCount / (en - beg);
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    cout << "Reactions per second: " << reacPerSecond << endl;
    log->setReacPerSecond(reacPerSecond);
    log->setNumberReacExecuted(reacCount);
}
DirectMethod::~DirectMethod()
{
}
