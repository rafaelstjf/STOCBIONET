#ifndef SSA_HPP
#define SSA_HPP

#include<string>
#include <iostream>
#include <stdlib.h>
#include "../include/Model.hpp"
#include "../include/DependencyGraph.hpp"
#include "../include/Utils.hpp"

#include <map>
using namespace std;

class SSA
{
public:
    virtual void perform(string filename, double simulTime, double beginTime) = 0;
    virtual bool checkSucess();
    virtual ~SSA();
    virtual void printResult();
protected:
    Utils* ut;
    DependencyGraph* dg;
    Model* model;
    double totalPropensity; //sum of all the propensities
    double currentTime; //current time of the simulation
    double beginTime; //time that the simulation begins
    int selectedReaction;
    string methodOutName;
    map<double, int*> x; //state dynamics
    double* propArray; //propensity array
    double simulTime; //simulation time
    int* specQuantity; //species quantity
    double reacPerSecond; //number of reactions executed per second
    bool sucess; //boolean variable used to check if the simulation was performed

    //functions
    virtual void initialization(string filename,  double simultime) = 0; //read the model and initialization data structures
    virtual void calcPropensity(); //calculate the propensity function for each reaction
    virtual void calcPropOne(int index);
    virtual void reacTimeGeneration() = 0;
    virtual void reacSelection() = 0;
    virtual void saveToFile();
    virtual void reacExecution() = 0;

};

#endif // SSA_H
