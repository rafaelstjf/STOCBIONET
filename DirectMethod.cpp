#include "DirectMethod.h"
DirectMethod::~DirectMethod()
{
}
void DirectMethod::perform(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
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
    initialize(filename);

}

void DirectMethod::initialize(string filename)
{
    double currentTime = 0.0;
    double t = 0.0;
    double selector = 0.0;
    int* x = new int[model->getSpecNumber()];
    for(int i = 0; i < model->getSpecNumber(); i++)
        x[i] = 0;
    int selectedReaction = 0;
    while(currentTime < simulTime)
    {
        calcPropensity();
        //generate simulation time
        double u1, u2;
        u1 = ut->getRandomNumber();
        t = (1.0/totalPropensity)*ut->ln(1.0/u1); //next time increase
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
        cout << "Selected reaction: " << selectedReaction << endl;
        //reaction execution
        for(int i = 0; i < model->getSpecNumber(); i++)
        {
            x[i] = x[i] + model->getStoiMatrix()[selectedReaction][i];
        }
        currentTime = currentTime + t; //change current time
        //check the dependencies of the selected reaction and update the propensity array
        int* deparray = dg->getDependencies(selectedReaction);
        int depSize = dg->getDependenciesSize(selectedReaction);
        for(int i = 0; i< depSize; i++)
        {
            cout << "   -> " << i << endl;
            double propOld = propArray[i];
            calcPropOne(i);
            totalPropensity = totalPropensity - propOld + propArray[i];
        }
    }
    for(int i = 0; i < model->getSpecNumber(); i++)
    {
        cout << x[i] << " : ";
    }
}

void DirectMethod::calcPropensity()
{
    //updates the entire array of propensities
    int sum = 0;
    totalPropensity = 0;
    for(int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 0;
        for(int j = 0; j < model->getSpecNumber(); j++)
        {
            sum+= ut->binomialCoefficient(specQuantity[j], model->getReactants()[i][j]);
        }
        propArray[i] = sum;
        totalPropensity+=  propArray[i];
    }
}
void DirectMethod::calcPropOne(int index)
{
    //updates the propensity of the selected reaction
    int sum = 0;
    for(int j = 0; j < model->getSpecNumber(); j++)
    {
        sum+= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);

    }
    propArray[index] = sum;

}
void DirectMethod::selectReaction()
{
}
