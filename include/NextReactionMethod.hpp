#ifndef NEXTREACTIONMETHOD_HPP
#define NEXTREACTIONMETHOD_HPP

#include <iostream>
#include <iomanip>
#include "../include/SSA.hpp"
#include "../include/IndexedPrioQueue.hpp"
#include "../include/HeapNode.hpp"
#include "../include/List.hpp"


using namespace std;

class NextReactionMethod : public SSA{
    public:
    virtual void perform(Model* model, double simulTime, double beginTime, long int seed);
    virtual ~NextReactionMethod();

    protected:
    virtual void initialization(Model* model, double simulTime, long int seed);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    double c;
    IndexedPrioQueue* queue;
    HeapNode* selectedNode;
    double* timePropZero; //time when ak becomes 0
    double* propNonZero;//last propensity != 0

};

#endif
