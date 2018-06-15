#ifndef NEXTREACTIONMETHODCAMILLO_HPP
#define NEXTREACTIONMETHODCAMILLO_HPP

#include <iostream>
#include <climits>
#include "../include/SSA.hpp"
#include "../include/IndexedPrioQueue.hpp"
#include "../include/HeapNode.hpp"
#include "../include/DependencyGraph.hpp"


#define inf INT_MAX
using namespace std;

class NextReactionMethodCamillo : public SSA{
    public:
    virtual void perform(string filename, double simulTime, double beginTime);
    virtual ~NextReactionMethodCamillo();

    protected:
    virtual void initialization(string filename, double simulTime);
    virtual void calcPropensity();
    virtual void calcPropOne(int index);
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
