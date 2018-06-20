#include "../include/Model.hpp"

Model::Model()
{
    reactants = NULL;
    products = NULL;
    delaysValue = NULL;
    delaysVariation = NULL;
    stoiMatrix = NULL;
    specNumber = 0;
    reacNumber = 0;
    specNameNumber.clear();
    modelLoaded = false;
}
Model::~Model()
{
    for(int i = 0; i < reacNumber; i++)
    {
        delete[] reactants[i];
        delete[] products[i];
        delete[] delaysValue[i];
        delete[] delaysVariation[i];
        delete[] stoiMatrix[i];
    }
    delete[] reactants;
    delete[] products;
    delete[] delaysValue;
    delete[] delaysVariation;
    delete[] stoiMatrix;
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
        /*cout << "Load model in debug mode?(y or n)" << endl;
        cin >> debug;
        debug == 'n';
        if (debug == 'y' or debug == 'Y')
            tr = new TReact(true);
        else
            tr = new TReact(false);
        */
        tr = new TReact(false);
        vector<Reaction*> reactions = tr->getReactions(text.str(), specNameNumber, specQuantity, modelRepresentation);
        text.clear();
        //delete tr;
        specNumber = specNameNumber.size();
        reacNumber = reactions.size();
        //Lines = reactions. Columns = species.
        reactants = new int *[reacNumber];
        products = new int *[reacNumber];
        delaysValue = new double *[reacNumber];
        delaysVariation = new double *[reacNumber];
        reacRate = new double[reacNumber];
        for (i = 0; i < reacNumber; i++)
        {
            reactants[i] = new int[specNumber];
            products[i] = new int[specNumber];
            delaysValue[i] = new double[specNumber];
            delaysVariation[i] = new double[specNumber];
        }
        //clears all the matrices
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
        cout << " * Reactants loaded" << endl;
        cout << " * Products loaded" << endl;
        for(i = 0; i < reacNumber; i++)
        {
            reacRate[i] = reactions[i]->getRate();
            delete reactions[i];
            //cout << "Reaction[" << i << "]: " << reacRate[i] << " ";
        }
        cout << " * Reaction rate constants loaded" << endl;

         /*
        cout << "Reactants" << endl;
        for(i = 0; i < reacNumber; i++)
        {

            for(j = 0; j < specNumber; j++)
                cout << reactants[i][j] << " ";
            cout << endl;

        }
        cout << "Products" << endl;
        for(i = 0; i < reacNumber; i++)
        {
            for(j = 0; j < specNumber; j++)
                cout << products[i][j] << " ";
            cout << endl;

        }
        */
        initialQuantity = new int[specNumber];
        map<string, long int>::iterator itQ = specNameNumber.begin();
        while(itQ != specNameNumber.end())
        {
            initialQuantity[itQ->second] = specQuantity.find(itQ->first)->second; //search the specie with the same name and set the quantity
            itQ++;
        }
        for(i = 0; i < specNumber; i++)
        {
            itQ = specNameNumber.begin();
            while(itQ != specNameNumber.end())
            {
                if(itQ->second == i)
                    break;
                itQ++;
            }
            //cout << itQ->first << " [" << initialQuantity[i] << "]" << endl;
        }
        cout << " * Species quantities loaded" << endl;
        //print model representation
        /*
        for(i = 0; i< modelRepresentation.size(); i++){
            cout << modelRepresentation[i] << endl;
        }*/

        buildStoichiometryMatrix();
        cout << " * Stoichiometry matrix loaded" << endl;
        /*
        for(i = 0; i < reacNumber; i++)
        {
            for(j = 0; j < specNumber; j++)
                cout << stoiMatrix[i][j] <<" ";
            cout << endl;
        }
        */
        cout << "Model loaded" << endl;
        modelLoaded = true;
        specQuantity.clear();
        reactions.clear();
    }
    else
    {
        cout << "file missing or incorrect!" << endl;
        modelLoaded = false;
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
void Model::buildStoichiometryMatrix()
{
    stoiMatrix = new int*[reacNumber];
    for(int i = 0; i < reacNumber; i++)
        stoiMatrix[i] = new int[specNumber];
    for(int i = 0; i < reacNumber; i++)
    {
        for(int j = 0; j < specNumber; j++)
        {
            stoiMatrix[i][j] = -1*reactants[i][j] + products[i][j];
        }
    }
}
int** Model::getStoiMatrix()
{
    return stoiMatrix;
}
