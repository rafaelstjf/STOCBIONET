#include "DirectMethod.h"
void DirectMethod::initialize(string filename)
{
    //instantiate the variables
    model = new Model(); //instantiate the model
    ut = new Utils();    //instantiate the utility class
    specQuantity = new int[model->getSpecNumber()];
    propArray = new double[model->getReacNumber()];
    this->simulTime = simulTime;
    totalPropensity = 0;
    //load both model and its depedency graph
    model->loadModel(filename);
    dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
    dg->printGraph();
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = model->getInitialQuantity()[i];
    }

}
void DirectMethod::perform(string filename, double simulTime)
{
    initialize(filename);     //instantiate the variables
    double beg = ut->getCurrentTime(); //begin
    //peform the simulation
    double currentTime = 0.0;
    double t = 0.0;
    double selector = 0.0;
    int *xArray;
    int selectedReaction = 0;
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
        double u1, u2;
        u1 = ut->getRandomNumber();
        u2 = ut->getRandomNumber();
        t = (1.0 / totalPropensity) * ut->ln(1.0 / u1); //next time increase
        //cout << (totalPropensity) << " : " << ut->ln(1.0 / u1) << "T: " << t << " C: " << currentTime << endl;
        //reaction selection
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
        //reaction execution
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[selectedReaction][i];
        }
        currentTime = currentTime + t;
        //check the dependencies of the selected reaction and update the propensity array
        int *deparray = dg->getDependencies(selectedReaction);
        int depSize = dg->getDependenciesSize(selectedReaction);
        for (int i = 0; i < depSize; i++)
        {
            calcPropOne(deparray[i]);
        }
    }
    double en = ut->getCurrentTime(); //end
    saveToFile();
    //printResult();
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
}
void DirectMethod::calcPropensity()
{
    //updates the entire array of propensities
    //propensity of a reaction i is: reaction rate * productory(n=0; n=numSpecies) of binomialcoefficient(SpecQuantity[n],reactants[i][n]
    int sum = 1;
    totalPropensity = 0;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 1;
        for (int j = 0; j < model->getSpecNumber(); j++)
        {
            sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[i][j]);
        }
        propArray[i] = model->getReacRateArray()[i] * sum;
        totalPropensity += propArray[i];
    }
}
void DirectMethod::calcPropOne(int index)
{
    //updates the propensity of the selected reaction
    int sum = 1;
    float propOld = propArray[index];
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
    totalPropensity = totalPropensity - propOld + propArray[index];
}
void DirectMethod::saveToFile()
{
    stringstream buffer;
    map<string, long int> speciesNameNumber = model->getSpecNameNumber();
    map<double, int*>::iterator itX = x.begin();
    map<string, long int>::iterator itSpecies = speciesNameNumber.begin();
    //get the name of the species
    string names[speciesNameNumber.size()];
    while(itSpecies!= speciesNameNumber.end())
    {
        names[itSpecies->second] = itSpecies->first;
        itSpecies++;
    }
    buffer.clear();
    buffer << "Time; ";
    for(int i = 0; i < speciesNameNumber.size(); i++)
    {
        buffer << names[i];
        if(i<speciesNameNumber.size()-1)
            buffer << "; ";
    }
    buffer << '\n';
    while(itX != x.end())
    {
        int* a = itX->second;
        buffer << itX->first << "; ";
        for(int i = 0; i < model->getSpecNumber(); i++)
        {
            buffer << a[i];
            if(i< model->getSpecNumber()-1)
                buffer << "; ";
        }
        buffer << '\n';
        itX++;
    }
    ut->saveToCSV(buffer.str(), "DM_output");
}
void DirectMethod::printResult()
{
    map<double, int*>::iterator it = x.begin();
    while(it != x.end())
    {
        int* a = it->second;
        cout << "Time: " << it->first << endl;
        for(int i = 0; i < model->getSpecNumber(); i++)
        {
            cout << a[i];
            if(i<model->getSpecNumber() - 1)
                cout << ": ";
        }
        cout << endl;
        it++;
    }
}
DirectMethod::~DirectMethod()
{
    delete dg;
    delete model;
    delete ut;
    //delete[] specQuantity;
    //delete[] propArray;
}
