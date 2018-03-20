#include "DirectMethod.h"
DirectMethod::~DirectMethod()
{
    delete ut;
}
void DirectMethod::perform(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    specQuantity = new int[model->getSpecNumber()];
    propArray = new double[model->getReacNumber()];
    this->simulTime = simulTime;
    model->loadModel(filename);
    dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
    dg->printGraph();
    for(int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = model->getInitialQuantity()[i];
    }
    totalPropensity = 0;
    double beg = ut->getCurrentTime();
    initialize(filename);
    double en = ut->getCurrentTime();
    cout << "\nFinished with " << en-beg << " seconds." << endl;

}

void DirectMethod::initialize(string filename)
{
    double currentTime = 0.0;
    stringstream buffer;
    double t = 0.0;
    double selector = 0.0;
    double u1 = 0.0, u2 = 0.0;
    int* x = new int[model->getSpecNumber()];
    for(int i = 0; i < model->getSpecNumber(); i++)
        x[i] = specQuantity[i];
    int selectedReaction = 0;
    calcPropensity();
    while(currentTime < simulTime)
    {
         //generate simulation time
        u1 = ut->getRandomNumber();
        u2 = ut->getRandomNumber();
        t = (1.0/totalPropensity)*ut->ln(1.0/u1); //next time increase
        //reaction selection
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
            x[i] = x[i] + model->getStoiMatrix()[selectedReaction][i];
            specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[selectedReaction][i] ;
        }
        currentTime = currentTime + t;
        //check the dependencies of the selected reaction and update the propensity array
        int* deparray = dg->getDependencies(selectedReaction);
        int depSize = dg->getDependenciesSize(selectedReaction);
        for(int i = 0; i< depSize; i++)
        {
           double propOld = propArray[deparray[i]];
            calcPropOne(deparray[i]);
            totalPropensity = totalPropensity - propOld + propArray[deparray[i]];
        }
        buffer <<currentTime << ";";
        for(int i = 0; i < model->getSpecNumber(); i++){
            buffer << x[i];
            if(i < model->getSpecNumber() - 1)
                buffer << ";";
        }
        buffer << "\n";
    }
    ut->saveToCSV(buffer.str());
    for(int i = 0; i < model->getSpecNumber(); i++)
    {
      cout << specQuantity[i] << " : ";
    }

}

void DirectMethod::calcPropensity()
{
    //updates the entire array of propensities
    //propensity of a reaction i is: reaction rate * multiplicand(n=0; n=numSpecies) of binomialcoefficient(SpecQuantity[n],reactants[i][n]
    int sum = 1;
    totalPropensity = 0;
    for(int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 1;
        for(int j = 0; j < model->getSpecNumber(); j++)
        {
            if(model->getReactants()[i][j]!=0)
                sum*= ut->binomialCoefficient(specQuantity[j], model->getReactants()[i][j]);
        }
        propArray[i] = sum*model->getReacRateArray()[i];
        totalPropensity+=  propArray[i];
    }
}
void DirectMethod::calcPropOne(int index)
{
    //updates the propensity of the selected reaction
    int sum = 1;
    for(int j = 0; j < model->getSpecNumber(); j++)
    {
         if(model->getReactants()[index][j]!=0)
            sum*= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);

    }
    propArray[index] = sum*model->getReacRateArray()[index];

}
void DirectMethod::selectReaction()
{
}
