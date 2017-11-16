#ifndef DIRECTMETHOD_H
#define DIRECTMETHOD_H

#include <iostream>
#include "WithoutDelay.h"


using namespace std;

class DirectMethod : public WithoutDelay
{
public:
    DirectMethod();
    virtual ~DirectMethod();
    void perform(string filename);

private:
    virtual void initialize(string filename); //read the model and initialize data structures
    virtual void calcPropensity(); //calculate the propensity function for each reaction
    virtual void genReactionTime(); //estimate the occurrence time for the next reaction
    virtual void selectReaction(); //select which reaction will occur next
};

#endif // DIRECTMETHOD_H
