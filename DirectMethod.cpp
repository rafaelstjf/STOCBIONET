#include "DirectMethod.h"

DirectMethod::DirectMethod()
{
    model = new Model();
}

DirectMethod::~DirectMethod()
{
}
void DirectMethod::perform(string filename)
{
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
