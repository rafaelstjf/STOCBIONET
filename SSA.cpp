#include "SSA.h"

SSA::SSA()
{
    model = new Model();
}

SSA::~SSA()
{
    delete model;
}
void SSA::loadModel(string filename)
{
    model->loadModel(filename);
}
