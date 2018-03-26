#include "DirectMethod.h"
DirectMethod::~DirectMethod()
{
    delete ut;
}
void DirectMethod::perform(string filename, double simulTime)
{
    model = new Model(); //instantiate the model
    ut = new Utils(); //instantiate the utility class
    specQuantity = new int[model->getSpecNumber()];
    propArray = new float[model->getReacNumber()];
    this->simulTime = simulTime;
    model->loadModel(filename);
    dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
    dg->printGraph();
    for(int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = model->getInitialQuantity()[i];
    }
    totalPropensity = 0;
    double beg = ut->getCurrentTime(); //begin
    initialize(filename);
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en-beg << " seconds." << endl;

}

void DirectMethod::initialize(string filename)
{
    double currentTime = 0.0;
    double t = 0.0;
    double selector = 0.0;
    int* xArray;
    int selectedReaction = 0;
    //calculate the reactions propensity
    calcPropensity();
    while(currentTime <= simulTime)
    {
        //save the current species quantities on the map
        xArray = new int[model->getSpecNumber()];
        for(int i = 0; i < model->getSpecNumber(); i++)
        {
            xArray[i] = 0;
            xArray[i] = specQuantity[i];

        }
        x.insert(make_pair(currentTime, xArray));

        //generate simulation time
        double u1, u2;
        u1 = ut->getRandomNumber();
        t = (1.0/totalPropensity)*ut->ln(1.0/u1); //next time increase
        cout << (totalPropensity) << " : " << ut->ln(1.0/u1)  << "T: " << t<< " C: " << currentTime << endl;
        //reaction selection
        u2 = ut->getRandomNumber();
        selector = totalPropensity*u2;
        for(int i = 0; i < model->getReacNumber(); i++)
        {
            selector = selector - propArray[i];
            if(selector <= 0.0)
            {
                selectedReaction = i;
                break;
            }
        }
        //reaction execution
        for(int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[selectedReaction][i];
        }
        currentTime = currentTime + t; //change current time
        //check the dependencies of the selected reaction and update the propensity array
        int* deparray = dg->getDependencies(selectedReaction);
        int depSize = dg->getDependenciesSize(selectedReaction);
        for(int i = 0; i< depSize; i++)
        {
            calcPropOne(deparray[i]);
        }
    }
    for(int i = 0; i< model->getSpecNumber(); i++)
        cout << specQuantity[i] << " : ";
    cout << endl;

}

void DirectMethod::calcPropensity()
{
    //updates the entire array of propensities
    int sum = 0;
    totalPropensity = 0;
    for(int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 1;
        for(int j = 0; j < model->getSpecNumber(); j++)
        {
            sum*= ut->binomialCoefficient(specQuantity[j], model->getReactants()[i][j]);
        }
        propArray[i] = model->getReacRateArray()[i]*sum;
        totalPropensity+= propArray[i];
    }
}
void DirectMethod::calcPropOne(int index)
{
    //updates the propensity of the selected reaction
    int sum = 1;
    float propOld = propArray[index];
    for(int j = 0; j < model->getSpecNumber(); j++)
    {
        sum*= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);

    }
    propArray[index] = model->getReacRateArray()[index]*sum;
    totalPropensity = totalPropensity - propOld + propArray[index];

}
