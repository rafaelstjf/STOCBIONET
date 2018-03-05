#ifndef SSA_H
#define SSA_H

#include<string>
#include <iostream>
#include <stdlib.h>
#include "Model.h"
#include "DependencyGraph.h"
using namespace std;

class SSA
{
public:
    SSA();
    virtual void perform(string filename) = 0;
    virtual ~SSA();
protected:
    Model* model;
    float* p; //propensity array
    //functions
    virtual void initialize(string filename) = 0; //read the model and initialize data structures
    virtual void calcPropensity() = 0; //calculate the propensity function for each reaction
    virtual void genReactionTime() = 0; //estimate the occurrence time for the next reaction
    virtual void selectReaction() = 0; //select which reaction will occur next
    void loadModel(string filename); //load the model using a input file

};

#endif // SSA_H
