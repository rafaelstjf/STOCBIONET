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
    SBMLReader reader;
    clock_t c;
    double start = 0.0, stop = 0.0;
    c = clock();
    start = (float)c / CLOCKS_PER_SEC;
    SBMLDocument *document;
    document = reader.readSBML(filename.c_str()); //read a sbml model
    model = document->getModel();
    c = clock();
    stop = (float)c / CLOCKS_PER_SEC;
    cout << "Direct Method." << endl;
    cout << "Model: " << filename << endl;
    cout << "Reactions: " << model->getNumReactions() << endl;
    cout << "Species: " << model->getNumSpecies() << endl;
    cout << "Validation errors: " << document->getNumErrors() << endl;
    cout << "Reading time: " << (stop - start) << endl;
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
