#ifndef SSA_H
#define SSA_H

#include<string>
#include <iostream>
#include <stdlib.h>
#include "DependencyGraph.h"
#include <sbml/SBMLTypes.h> //sbml external library
#include <sbml/common/extern.h>
#include <ctime>
#include "Specie.h"

using namespace std;

class SSA
{
public:
    SSA();
    void perform(string filename);
    virtual ~SSA();
protected:
    typedef struct Reactions
    {
        // each reaction has 2 matrix(products and reactants)
        int** reactants;
        int** products;
        int numReactions;
        int numSpecies;

    } Reactions;
    Reactions* reactions; //reactions of the model
    int* k; //reaction rate constant
    float* a0; //propensity array
    Model* model; //creates a pointer for a document type
private:

    virtual void initialize(string filename) = 0; //read the model and initialize data structures
    virtual void calcPropensity() = 0; //calculate the propensity function for each reaction
    virtual void genReactionTime() = 0; //estimate the occurrence time for the next reaction
    virtual void selectReaction() = 0; //select which reaction will occur next
    void importFromModel(); //create the reactions structure using the sbml model

};

#endif // SSA_H
