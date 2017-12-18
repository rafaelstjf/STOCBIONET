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
    void initialize(string filename); //read the model and initialize data structures
    void calcPropensity(); //calculate the propensity function for each reaction
    void genReactionTime(); //estimate the occurrence time for the next reaction
    void selectReaction(); //select which reaction will occur next
};

#endif // DIRECTMETHOD_H
