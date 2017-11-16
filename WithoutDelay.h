#ifndef WITHOUTDELAY_H
#define WITHOUTDELAY_H
#include "SSA.h"
#include "DependencyGraph.h"
#include <iostream>


using namespace std;

class WithoutDelay :public SSA
{
public:
    WithoutDelay();
    virtual ~WithoutDelay();
    void perform(string filename);

protected:
        DependencyGraph* dg;
private:
    virtual void initialize(string filename) = 0; //read the model and initialize data structures
    virtual void calcPropensity() = 0; //calculate the propensity function for each reaction
    virtual void genReactionTime() = 0; //estimate the occurrence time for the next reaction
    virtual void selectReaction() = 0; //select which reaction will occur next
};

#endif // WITHOUTDELAY_H
