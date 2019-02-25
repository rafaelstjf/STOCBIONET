#ifndef NEXTREACTIONMETHODCOMPACT_HPP
#define NEXTREACTIONMETHODCOMPACT_HPP
#include <iostream>
#include <climits>
#include "SSA.hpp"
#include "HeapNode.hpp"
#include "IndexedPrioQueue.hpp"
#include "List.hpp"

using namespace std;

class NextReactionMethodCompact : public SSA
{
public:
    virtual void perform(Model* model, double maximumTime, double initialTime, long int seed);
    virtual ~NextReactionMethodCompact();

protected:
    virtual void initialization(Model* model, double maximumTime, double initialTime, long int seed);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    IndexedPrioQueue* queue; //priority queue used to store the absolute time of each reaction
    double* timePropZero;
    double* propNonZero;
    double* delta;
    double cOld;
    HeapNode* selectedNode; //used to store the selected reaction index and time

};
#endif
