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
void SSA::importFromModel(){
    cout << "Importing from model" << endl;
    ListOfReactions* listReac = model->getListOfReactions(); //get all the reactions
    ListOfSpecies* listspe = model->getListOfSpecies(); //get all the species
    Specie* listIntSpec = new Specie(listspe->size()); //class to save the species in DG index
    for(int i = 0; i<listspe->size(); i++)
        listIntSpec->insertSpecie(listspe->get(i)->getId());
    reactions = new Reactions;
    reactions->numReactions = listReac->size(); //get the number of reactions
    reactions->numSpecies = listspe->size(); //get the number of species
    // [species][reactions]
    int** reactants = new int*[reactions->numSpecies];
    int** products = new int*[reactions->numSpecies];
    for(int i = 0; i< reactions->numSpecies; i++){
        reactants[i] = new int[reactions->numReactions];
        products[i] = new int[reactions->numReactions];
    }
    //setting 0 in all elements
    for(int i = 0; i<reactions->numSpecies;i++){
        for(int j = 0; j<reactions->numReactions; j++){
            reactants[i][j] = 0;
            products[i][j] = 0;
        }
    }
    for(int i = 0; i<reactions->numReactions;i++){
        ListOfSpeciesReferences* listReactants = listReac->get(i)->getListOfReactants();
        ListOfSpeciesReferences* listProducts = listReac->get(i)->getListOfProducts();
        for(int j = 0; j<listReactants->size(); j++){
            int index = listIntSpec->getIndexById(listReactants->get(j)->getId());
            reactants[index][i] = 1;
        }
        for(int j = 0; j<listProducts->size(); j++){
            int index = listIntSpec->getIndexById(listProducts->get(j)->getId());
            products[index][i] = 1;
        }
    }
    reactions->reactants = reactants;
    reactions->products = products;
    cout << "Model successfully imported" << endl;
}