#ifndef MODIFIEDNEXTREACTIONMETHOD_HPP
#define MODIFIEDNEXTREACTIONMETHOD_HPP

#include <iostream>
#include <climits>
#include "../include/SSA.hpp"
#include "../include/IndexedPrioQueue.hpp"
#include "../include/HeapNode.hpp"


#define inf INT_MAX
using namespace std;

class ModifiedNextReactionMethod : public SSA{
    public:
    virtual void perform(string filename, double simulTime, double beginTime);
    virtual ~ModifiedNextReactionMethod();

    protected:
    virtual void initialization(string filename, double simulTime);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    IndexedPrioQueue* queue;
    HeapNode* selectedNode;
    double* T;
    double* P;

};

#endif
