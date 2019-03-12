#ifndef OPTIMIZEDDIRECTMETHOD_HPP
#define OPTIMIZEDDIRECTMETHOD_HPP

#include <iostream>
#include <climits>
#include "SSA.hpp"

using namespace std;

class OptimizedDirectMethod : public SSA{
    public:
    virtual void perform(Model* model, double maximumTime, double initialTime, long int seed);
    virtual ~OptimizedDirectMethod();

    protected:
    virtual void initialization(Model* model, double maximumTime, double initialTime, long int seed);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    virtual void preSimul();
    bool pSimul;
    int* reactionSO;
    double t;
    int reactionSOindex;
};

#endif