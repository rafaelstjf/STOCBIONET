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
    for(int i = 0; i < model->getSpecNumber(); i++){
        specQuantity[i] = model->getInitialQuantity()[i];
    }
    totalPropensity = 0;
    initialize(filename);

}

void DirectMethod::initialize(string filename)
{
    double currentTime = 0.0;
    double t = 0.0;
    while(currentTime < simulTime){
        calcPropensity();
        //generate simulation time

        currentTime++;
    }


}

void DirectMethod::calcPropensity()
{
    int sum = 0;
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
void DirectMethod::selectReaction()
{
}
