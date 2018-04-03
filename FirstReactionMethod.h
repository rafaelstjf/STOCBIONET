#ifndef FIRSTREACTIONMETHOD_H
#define FIRSTREACTIONMETHOD_H

#include <iostream>
#include "SSA.h"

using namespace std;

class FirstReactionMethod : public SSA
{
public:
    void perform(string filename, double simulTime);
    FirstReactionMethod();
    virtual ~FirstReactionMethod();

protected:

private:
    void initialize(string filename); //read the model and initialize data structures
    //void calcPropensity(); //calculate the propensity function for all the reactions
    //void calcPropOne(int index);
};

#endif // FIRSTREACTIONMETHOD_H
