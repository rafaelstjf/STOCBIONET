#ifndef NEXTREACTIONMETHOD_HPP
#define NEXTREACTIONMETHOD_HPP

#include <iostream>
#include <iomanip>
#include "SSA.hpp"
#include "IndexedPrioQueue.hpp"
#include "HeapNode.hpp"
#include "List.hpp"


using namespace std;

class NextReactionMethod : public SSA{
    public:
    virtual void perform(Model* model, double maximumTime, double initialTime, long int seed);
    virtual ~NextReactionMethod();

    protected:
    virtual void initialization(Model* model, double maximumTime, double initialTime, long int seed);
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
