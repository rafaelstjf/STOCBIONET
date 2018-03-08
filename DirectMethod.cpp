#include "DirectMethod.h"
DirectMethod::~DirectMethod()
{
}
void DirectMethod::perform(string filename)
{
    model = new model;
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
