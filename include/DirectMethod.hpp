#ifndef DIRECTMETHOD_HPP
#define DIRECTMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"

using namespace std;

class DirectMethod : public SSA
{
public:

    void perform(string filename, double simulTime);
    virtual ~DirectMethod();

private:
    double t;
    int selectedReaction;
    void initialization(string filename,  double simultime); //read the model and initialization data structures
    void calcPropensity(); //calculate the propensity function for all the reactions
    void calcPropOne(int index);
    void printResult();
    void saveToFile();
    void reacTimeGeneration();
    void reacSelection();
    void reacExecution();

};

#endif // DIRECTMETHOD_H
