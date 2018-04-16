#ifndef FIRSTREACTIONMETHOD_H
#define FIRSTREACTIONMETHOD_H

#include <iostream>
#include "SSA.h"

using namespace std;

class FirstReactionMethod: public SSA
{
public:
    void perform(string filename, double simulTime);
    virtual ~FirstReactionMethod();

protected:

private:
    void initialize(string filename, double simulTime); //read the model and initialize data structures
    void calcPropensity(); //calculate the propensity function for all the reactions
    virtual void printResult();
    virtual void saveToFile();
    void calcPropOne(int index);
    double* t;
};

#endif // FIRSTREACTIONMETHOD_H
