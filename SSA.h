#ifndef SSA_H
#define SSA_H

#include<string>
#include <iostream>
#include <stdlib.h>
#include "Model.h"
#include "DependencyGraph.h"
#include "Utils.h"
using namespace std;

class SSA
{
public:
    virtual void perform(string filename, double simulTime) = 0;
    virtual ~SSA();
protected:
    Utils* ut;
    DependencyGraph* dg;
    Model* model;
    double* propArray; //propensity array
    double simulTime; //simulation time
    int* specQuantity; //species quantity
    double totalPropensity; //sum of all the propensities
    //functions
    virtual void initialize(string filename) = 0; //read the model and initialize data structures
    virtual void calcPropensity() = 0; //calculate the propensity function for each reaction
    virtual void selectReaction() = 0; //select which reaction will occur next

};

#endif // SSA_H
