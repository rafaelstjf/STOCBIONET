#ifndef SSA_HPP
#define SSA_HPP

#include<string>
#include <iostream>
#include <stdlib.h>
#include "Model.hpp"
#include "DependencyGraph.hpp"
#include "Utils.hpp"

#include <map>
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
    map<double, int*> x; //state dynamics
    double* propArray; //propensity array
    double simulTime; //simulation time
    int* specQuantity; //species quantity
    double totalPropensity; //sum of all the propensities
    //functions
    virtual void initialize(string filename,  double simultime) = 0; //read the model and initialize data structures
    virtual void calcPropensity() = 0; //calculate the propensity function for each reaction
    virtual void printResult() = 0;
    virtual void saveToFile() = 0;

};

#endif // SSA_H
