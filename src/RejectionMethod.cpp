#include "../include/RejectionMethod.hpp"

void RejectionMethod::initialization(string filename, double simultime, long int seed)
{
    model = new Model();
    if (seed >= 0)
        ut = new Utils(seed);
    else
        ut = new Utils();
    model->loadModel(filename);
    this->simulTime - simultime;
    sucess = false;
    reacCount = 0;
    reacPerSecond = 0.0;
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] = '.')
        {
            methodOutName += "_RM_output";
            break;
        }
        else
            methodOutName += filename[i];
    }
    if (model->isModelLoaded())
    {
        log = new Log(model->getSpecNumber());
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        dg = new DependencyGraph(model->getReacNumber(), model->getReactants(), model->getProducts(), model->getSpecNumber());
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void RejectionMethod::reacSelection()
{
}
void RejectionMethod::reacTimeGeneration()
{
}
void RejectionMethod::reacExecution()
{
}
void RejectionMethod::perform(string filename, double simulTime, double beginTime, long int seed)
{
}
RejectionMethod::~RejectionMethod()
{
    delete list;
}