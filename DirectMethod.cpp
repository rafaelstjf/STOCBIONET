#include "DirectMethod.h"
DirectMethod::~DirectMethod()
{
}
void DirectMethod::perform(string filename, simulTime)
{
    model = new Model();
    this->simulTime = simulTime;
    initialize(filename);
}

void DirectMethod::initialize(string filename)
{
    model->loadModel(filename);

}

void DirectMethod::calcPropensity()
{

}

void DirectMethod::genReactionTime()
{
}

void DirectMethod::selectReaction()
{
}
