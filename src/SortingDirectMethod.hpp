#ifndef SORTINGDIRECTMETHOD_HPP
#define SORTINGDIRECTMETHOD_HPP

#include <iostream>
#include <climits>
#include "SSA.hpp"

using namespace std;
class SortingDirectMethod : public SSA{
    public:
    virtual void perform(Model* model, double maximumTime, double initialTime, long int seed);
    virtual ~SortingDirectMethod();

    protected:
    virtual void initialization(Model* model, double maximumTime, double initialTime, long int seed);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    int* reactionSO; //reaction search order
    double t;
    int reactionSOindex;
};
#endif