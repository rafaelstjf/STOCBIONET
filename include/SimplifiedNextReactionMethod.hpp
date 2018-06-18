#ifndef SIMPLIFIEDNEXTREACTIONMETHOD_HPP
#define SIMPLIFIEDNEXTREACTIONMETHOD_HPP

#include <iostream>
#include <climits>
#include "../include/SSA.hpp"
#include "../include/IndexedPrioQueue.hpp"
#include "../include/HeapNode.hpp"


#define inf INT_MAX
using namespace std;

class SimplifiedNextReactionMethod : public SSA{
    public:
    virtual void perform(string filename, double simulTime, double beginTime);
    virtual ~SimplifiedNextReactionMethod();

    protected:
    virtual void initialization(string filename, double simulTime);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    IndexedPrioQueue* queue;
    HeapNode* selectedNode;
    double* T;
    double* P;
    double* U;

};

#endif
