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
    modelLoaded = false;
}
Model::~Model()
{
}
void Model::loadModel(string filename)
{
    cout << "Loading model" << endl;
    fstream inFile;
    vector<SpecieQuantity*> sQ;
    vector<SpecieQuantity*> sQ2;
    map<string, long int>specQuantity;
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
        vector<Reaction*> reactions = tr->getReactions(text.str(), specNameNumber, specQuantity, modelRepresentation);
        specNumber = specNameNumber.size();
        reacNumber = reactions.size();
        //Lines = reactions. Columns = species.
        reactants = new int *[reacNumber];
        products = new int *[reacNumber];
        delaysValue = new double *[reacNumber];
        delaysVariation = new double *[reacNumber];
        for (i = 0; i < reacNumber; i++)
        {
            reactants[i] = new int[specNumber];
            products[i] = new int[specNumber];
            delaysValue[i] = new double[specNumber];
            delaysVariation[i] = new double[specNumber];
        }
        for (i = 0; i < reacNumber; i++)
        {
            for (j = 0; j < specNumber; j++)
            {
                reactants[i][j] = 0;
                products[i][j] = 0;
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
            sQ2 = r->getProducts();
            for (j = 0; j < sQ2.size(); j++)
            {
                products[i][sQ2[j]->getSpecie()->getNumber()] = sQ2[j]->getQuantity();
                if (sQ2[j]->getDelay()->getValue() > 0.0)
                    delaysValue[i][sQ2[j]->getSpecie()->getNumber()] = sQ2[j]->getDelay()->getValue();
                if (sQ2[j]->getDelay()->getVariation() > 0.0)
                    delaysValue[i][sQ2[j]->getSpecie()->getNumber()] = sQ2[j]->getDelay()->getVariation();
            }
        }
         reacRate = new double[reacNumber];
        for(i = 0; i < reacNumber; i++){
            reacRate[i] = reactions[i]->getRate();
        }
        cout << "Reactants" << endl;
        for(i = 0; i < reacNumber; i++){
            for(j = 0; j < specNumber; j++)
                cout << reactants[i][j] << " ";
            cout << endl;
        }
        cout << "Products" << endl;
        for(i = 0; i < reacNumber; i++){
            for(j = 0; j < specNumber; j++)
                cout << products[i][j] << " ";
            cout << endl;
        }
        cout << "Species quantities" << endl;
        initialQuantity = new int[specNumber];
        map<string, long int>::iterator itQ = specNameNumber.begin();
        while(itQ != specNameNumber.end()){
            initialQuantity[itQ->second] = specQuantity.find(itQ->first)->second; //search the specie with the same name and set the quantity
            itQ++;
        }
        for(i = 0; i < specNumber; i++){
            cout << "[" << initialQuantity[i] << "]";
        }
        cout << endl;
        cout << "Model loaded" << endl;
        modelLoaded = true;
        reactions.clear();
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
    return specNumber;
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
map<string, long int> Model::getSpecNameNumber()
{
    return specNameNumber;
}
int* Model::getInitialQuantity()
{
    return initialQuantity;
}
double* Model::getReacRateArray()
{
    return reacRate;
}
