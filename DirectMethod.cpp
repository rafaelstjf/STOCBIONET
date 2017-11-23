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

    //test
    int index  = 0;
    ListOfSpeciesReferences *listReactants;
    ListOfSpeciesReferences *listProducts;
    cout << "Importing from model" << endl;
    ListOfReactions *listReac = model->getListOfReactions(); //get all the reactions
    ListOfSpecies *listspe = model->getListOfSpecies();      //get all the species
    cout << "Extracting species' ID" << endl;
    Specie *listIntSpec = new Specie(listspe->size()); //class to save the species in DG index
    for (int i = 0; i < listspe->size(); i++)
        listIntSpec->insertSpecie(listspe->get(i)->getId());
    reactions = new Reactions;
    reactions->numReactions = listReac->size(); //get the number of reactions
    reactions->numSpecies = listspe->size();    //get the number of species
    // [species][reactions]
    cout << "Creating reactants and products arrays" << endl;
    int **reactants = new int *[reactions->numSpecies];
    int **products = new int *[reactions->numSpecies];
    for (int i = 0; i < reactions->numSpecies; i++)
    {
        reactants[i] = new int[reactions->numReactions];
        products[i] = new int[reactions->numReactions];
    }
    //setting 0 in all elements
    for (int i = 0; i < reactions->numSpecies; i++)
    {
        for (int j = 0; j < reactions->numReactions; j++)
        {
            reactants[i][j] = 0;
            products[i][j] = 0;
        }
    }
    cout << "Extracting reactants and products" << endl;
    for (int i = 0; i < reactions->numReactions; i++)
    {
       listReactants = listReac->get(i)->getListOfReactants();
       listProducts = listReac->get(i)->getListOfProducts();
        for (int j = 0; j < listReactants->size(); j++)
        {
            
            index = listIntSpec->getIndexById(listReactants->get(j)->getId());
            cout << listReactants->get(j)->getId() << endl;
            if (index != -1)
                reactants[index][i] = 1;
            else
                cout << "Invalid index" << endl;
        }
        for (int j = 0; j < listProducts->size(); j++)
        {
            index = listIntSpec->getIndexById(listProducts->get(j)->getId());
            if (index != -1)
                products[index][i] = 1;
            else
                cout << "Invalid index" << endl;
        }
    }
    reactions->reactants = reactants;
    reactions->products = products;
    cout << "Model successfully imported" << endl;
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
