#include "DirectMethod.h"

DirectMethod::DirectMethod()
{
    model = NULL;
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
    readModel(filename);
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
