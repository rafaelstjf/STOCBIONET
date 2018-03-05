#include "Model.h"

Model::Model()
{
    reactants = NULL;
    products = NULL;
    delaysValue = NULL;
    delaysVariation = NULL;
    specNumber = 0;
    reacNumber = 0;
    specNameNumber.clear();
    specQuantity.clear();
    modelLoaded = false;
}
Model::~Model()
{
}
void Model::loadModel(string filename)
{
    cout << "Loading model" << endl;
    fstream inFile;
    TReact *tr;
    char debug;
    stringstream text;
    int i;
    int j;
    inFile.open(filename, fstream::in);
    if (inFile.is_open())
    {
        cout << "Reading the file..." << endl;
        text << inFile.rdbuf();
        cout << "Read in debug mode?(y or n)" << endl;
        cin >> debug;
        if (debug == 'y' or debug == 'Y')
            tr = new TReact(true);
        else
            tr = new TReact(false);
        vector<Reaction> reactions = tr->getReactions(text.str(), speciesNumber, specQuantity, modelRepresentation);
        specNumber = speciesNumber.size();
        reacNumber = reactions.size();
        reactants = new int *[reacNumber];
        products = new int *[reacNumber];
        delaysValue = new double *[reacNumber];
        delaysVariation = new double *[reacNumber];
        for (i = 0; i < reacNumber; i++)
        {
            reactants[i] = new int[specNumber];
            reactants[i] = new int[specNumber];
            delaysValue[i] = new double[specNumber];
            delaysVariation[i] = new double[specNumber];
        }
        for (i = 0; i < reacNumber; i++)
        {
            for (j = 0; j < specNumber; j++)
            {
                reactants[i][j] = 0;
                reactants[i][j] = 0;
                delaysValue[i][j] = 0.0;
                delaysVariation[i][j] = 0.0;
            }
        }
        for (i = 0; i < reactions.size(); i++)
        {
            Reaction *r = reactions[i];
            sQ = r->getReactants();
            for (j = 0; j < sQ.size(); j++)
                reactants[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getQuantity();
            sQ = r->getProducts();
            for (j = 0; j < sQ.size(); j++)
            {
                products[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getQuantity();
                if (sQ[j]->getDelay()->getValue() > 0.0)
                    delaysValue[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getDelay()->getValue();
                if (sQ[j]->getDelay()->getVariation() > 0.0)
                    delaysValue[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getDelay()->getVariation();
            }
        }
        cout << "Model loaded" << endl;
        modelLoaded = true;
    }
    else
    {
        cout << "file missing or incorrect!" << endl;
    }
}
int **Model::getReactants()
{
    return reactants;
}
int **Model::getProducts()
{
    return products;
}
double **Model::getDelaysValue()
{
    return delaysValue;
}
double **Model::getDelaysVariation()
{
    return delaysVariation;
}
int Model::getSpecNumber()
{
    return speciesNumber;
}
int Model::getReacNumber()
{
    return reacNumber;
}
vector<string> Model::getModelRepresentation()
{
    return modelRepresentation;
}
bool Model::isModelLoaded()
{
    return modelLoaded;
}