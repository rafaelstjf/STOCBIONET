#include "SSA.h"


SSA::SSA()
{
    //ctor
}

SSA::~SSA()
{
    //dtor
}
SSA::DependencyGraph* generateDG(){
    ListOfReactions* listReac = model->getListOfReactions(); //get all the reactions
    ListOfSpecies* listEsp = model->getListOfSpecies(); //get all the species
    int numReactions = listReac->size(); //get the number of reactions
    int numSpec = listEsp->size(); //get the number of species
        
}