#include "SSA.h"

SSA::SSA()
{
    //ctor
    reactions = NULL;
}

SSA::~SSA()
{
    delete reactions;
}
void SSA::readModel(string filename)
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
    importFromModel();
}
void SSA::importFromModel()
{
    int index = 0;
    bool sucess = true;
    bool debug = true;
    ListOfSpeciesReferences *listReactants;
    ListOfSpeciesReferences *listProducts;
    cout << "----------------------------------------------" << endl;
    cout << "Importing from model" << endl;
    ListOfReactions *listReac = model->getListOfReactions(); //get all the reactions
    ListOfSpecies *listspe = model->getListOfSpecies();      //get all the species
    cout << "Extracting species' ID" << endl;
    Specie *listIntSpec = new Specie(listspe->size()); //class to save the species in DG index
    for (int i = 0; i < listspe->size(); i++)
    {
        listIntSpec->insertSpecie(listspe->get(i)->getId());
    }
    reactions = new Reactions;
    reactions->numReactions = listReac->size(); //get the number of reactions
    reactions->numSpecies = listspe->size();    //get the number of species
    // [species][reactions]
    cout << "Creating reactants and products arrays" << endl;
    double **reactants = new double *[reactions->numSpecies];
    double **products = new double *[reactions->numSpecies];
    for (int i = 0; i < reactions->numSpecies; i++)
    {
        reactants[i] = new double[reactions->numReactions];
        products[i] = new double[reactions->numReactions];
    }
    //setting 0 in all elements
    for (int i = 0; i < reactions->numSpecies; i++)
    {
        for (int j = 0; j < reactions->numReactions; j++)
        {
            reactants[i][j] = 0.0;
            products[i][j] = 0.0;
        }
    }
    cout << "Extracting reactants and products" << endl;
    for (int i = 0; i < reactions->numReactions; i++)
    {
        listReactants = listReac->get(i)->getListOfReactants();
        listProducts = listReac->get(i)->getListOfProducts();
        for (int j = 0; j < listReactants->size(); j++)
        {

            index = listIntSpec->getIndexById(listReactants->get(j)->getSpecies()); //get the specie of the reactant j
            if (index != -1)
                reactants[index][i] = model->getReaction(i)->getReactant(j)->getStoichiometry(); //get the stoichiometry
            else
            {
                cout << "Invalid index while extracting reactant[" << j << "]" << endl;
                sucess = false;
            }
        }
        for (int j = 0; j < listProducts->size(); j++)
        {
            index = listIntSpec->getIndexById(listProducts->get(j)->getSpecies()); //get the specie of the product j
            if (index != -1)
                products[index][i] = model->getReaction(i)->getProduct(j)->getStoichiometry(); //get the stoichiometry
            else
            {
                cout << "Invalid index while extracting product[" << j << "]" << endl;
                sucess = false;
            }
        }
    }
    reactions->reactants = reactants;
    reactions->products = products;
    if (sucess)
        cout << "Model successfully imported" << endl;
    if (debug)
    {
        //print the product and reactant matrix if it's in debug mode
        cout << "Reactants" << endl;
        for (int i = 0; i <reactions->numSpecies; i++)
        {
            for (int j = 0;j < reactions -> numReactions; j++){
                cout << reactions->reactants[i][j] << " ";
            }
            cout << endl;
        }
        cout << "--------------------------------" << endl;
        cout << "Products" << endl;
        for (int i = 0; i <reactions->numSpecies; i++)
        {
            for (int j = 0;j < reactions -> numReactions; j++){
                cout << reactions->products[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Error!" << endl;
        exit(-1);
    }
}