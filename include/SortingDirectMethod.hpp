#ifndef SORTINGDIRECTMETHOD_HPP
#define SORTINGDIRECTMETHOD_HPP

#include <iostream>
#include <climits>
#include "../include/SSA.hpp"

using namespace std;
class SortingDirectMethod : public SSA{
    public:
    virtual void perform(Model* model, double simulTime, double beginTime, long int seed);
    virtual ~SortingDirectMethod();

    protected:
    virtual void initialization(Model* model, double simulTime, long int seed);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    int* reactionSO; //reaction search order
    double t;
    int reactionSOindex;
};
#endif