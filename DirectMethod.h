#ifndef DIRECTMETHOD_H
#define DIRECTMETHOD_H

#include <iostream>
#include "SSA.h"

using namespace std;

class DirectMethod : public SSA
{
public:

    void perform(string filename, double simulTime);
    virtual ~DirectMethod();

private:
    void initialize(string filename); //read the model and initialize data structures
    void calcPropensity(); //calculate the propensity function for all the reactions
    void selectReaction(); //select which reaction will occur next
    void calcPropOne(int index);

};

#endif // DIRECTMETHOD_H
