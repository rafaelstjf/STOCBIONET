#include "Model.hpp"
void Model::clear()
{
    reactants = NULL;
    products = NULL;
    delaysValue = NULL;
    delaysVariation = NULL;
    stoiMatrix = NULL;
    dg = nullptr;
    ddg = nullptr;
    specNumber = 0;
    reacNumber = 0;
    specNameNumber.clear();
    modelLoaded = false;
    filename = "";
}
Model::Model()
{
    clear();
}
Model::~Model()
{
    for (int i = 0; i < specNumber; i++)
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
    delete ddg;
    delete dg;
}
void Model::loadModel(string filename)
{
    this->filename = filename;
    cout << "Loading model: " << filename << endl;
    fstream inFile;
    vector<SpecieQuantity *> sQ;
    vector<SpecieQuantity *> sQ2;
    map<string, long int> specQuantity;
    TReact *tr;
    char debug;
    stringstream text;
    int i;
    int j;
    inFile.open(filename, fstream::in);
    if (inFile.is_open())
    {
        //cout << "Importing reactions..." << endl;
        text << inFile.rdbuf();
        tr = new TReact(false);
        vector<Reaction *> reactions = tr->getReactions(text.str(), specNameNumber, specQuantity, modelRepresentation);
        text.clear();
        specNumber = specNameNumber.size();
        reacNumber = reactions.size();
        //Lines = species; Columns = reactions
        reactants = new int *[specNumber];
        products = new int *[specNumber];
        delaysValue = new double *[specNumber];
        delaysVariation = new double *[specNumber];
        reacRate = new double[reacNumber];
        try
        {
            for (i = 0; i < specNumber; i++)
            {
                reactants[i] = new int[reacNumber];
                products[i] = new int[reacNumber];
                delaysValue[i] = new double[reacNumber];
                delaysVariation[i] = new double[reacNumber];
            }
        }
        catch (bad_alloc &b)
        {
            cout << "Insufficient memory! Aborting!" << endl;
            exit(1);
        }
        //clears all the matrices
        for (i = 0; i < specNumber; i++)
        {
            for (j = 0; j < reacNumber; j++)
            {
                reactants[i][j] = 0;
                products[i][j] = 0;
                delaysValue[i][j] = 0.0;
                delaysVariation[i][j] = 0.0;
            }
        }
        cout << " * Reactants and products... ";
        for (i = 0; i < reactions.size(); i++)
        {
            Reaction *r = reactions[i];
            sQ = r->getReactants();
            for (j = 0; j < sQ.size(); j++)
                reactants[sQ[j]->getSpecie()->getNumber()][i] = sQ[j]->getQuantity();
            sQ2 = r->getProducts();
            for (j = 0; j < sQ2.size(); j++)
            {
                int specInd = sQ2[j]->getSpecie()->getNumber();
                products[specInd][i] = sQ2[j]->getQuantity();
                if (sQ2[j]->getDelay()->getValue() > 0.0)
                    delaysValue[specInd][i] = sQ2[j]->getDelay()->getValue();
                if (sQ2[j]->getDelay()->getVariation() > 0.0)
                    delaysVariation[specInd][i] = sQ2[j]->getDelay()->getVariation();
            }
        }
        sQ.clear();
        sQ2.clear();
        cout << "loaded" << endl;
        cout << " * Reaction rate constants ... ";
        for (i = 0; i < reacNumber; i++)
        {
            reacRate[i] = reactions[i]->getRate();
        }
        cout << "loaded" << endl;
        cout << " * Species quantities... ";
        initialQuantity = new int[specNumber];
        map<string, long int>::iterator itQ = specNameNumber.begin();
        while (itQ != specNameNumber.end())
        {
            initialQuantity[itQ->second] = specQuantity.find(itQ->first)->second; //search the specie with the same name and set the quantity
            itQ++;
        }
        cout << "loaded" << endl;
        cout << " * Stoichiometry matrix... ";
        buildStoichiometryMatrix();
        cout << "loaded" << endl;

        modelLoaded = true;
        specQuantity.clear();
        for (int i = 0; i < reacNumber; i++)
        {
            delete reactions[i];
        }
        reactions.clear();
        delete tr;
        cout << " * Dependency graph.. ";
        buildDependencyGraphs();
        cout << "loaded" << endl;
        cout << "Model loaded" << endl;
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
int *Model::getInitialQuantity()
{
    return initialQuantity;
}
double *Model::getReacRateArray()
{
    return reacRate;
}
void Model::buildStoichiometryMatrix()
{
    stoiMatrix = new int *[specNumber];
    for (int i = 0; i < specNumber; i++)
        stoiMatrix[i] = new int[reacNumber];
    for (int i = 0; i < specNumber; i++)
    {
        for (int j = 0; j < reacNumber; j++)
        {
            stoiMatrix[i][j] = -1 * reactants[i][j] + products[i][j];
        }
    }
}
int **Model::getStoiMatrix()
{
    return stoiMatrix;
}
string Model::getFilename()
{
    return filename;
}
void Model::printModel()
{
    cout << "Reactants: " << endl;
    for (int i = 0; i < specNumber; i++)
    {
        for (int j = 0; j < reacNumber; j++)
        {
            cout << reactants[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Products: " << endl;
    for (int i = 0; i < specNumber; i++)
    {
        for (int j = 0; j < reacNumber; j++)
        {
            cout << products[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Delay Values: " << endl;
    for (int i = 0; i < specNumber; i++)
    {
        for (int j = 0; j < reacNumber; j++)
        {
            cout << delaysValue[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Delay Variation: " << endl;
    for (int i = 0; i < specNumber; i++)
    {
        for (int j = 0; j < reacNumber; j++)
        {
            cout << delaysVariation[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Reaction Rates: " << endl;
    for (int j = 0; j < reacNumber; j++)
    {
        cout << reacRate[j] << " ";
    }
    cout << endl;
}
void Model::buildDependencyGraphs()
{
    dg = new DependencyGraph(true, reacNumber, specNumber, reactants, products, delaysValue);
//    dgNoSelfEdges = new DependencyGraph(false, reacNumber, specNumber, reactants, products, delaysValue);
    ddg = new DelayedDependencyGraph(reacNumber, specNumber, reactants);
}
DependencyGraph *Model::getDG()
{
    return dg;
}
/*DependencyGraph *Model::getDGNoSelfEdge()
{
    return dgNoSelfEdges;
}*/
DelayedDependencyGraph *Model::getDDG()
{
    return ddg;
}