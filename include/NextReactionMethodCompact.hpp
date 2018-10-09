#ifndef NEXTREACTIONMETHODCOMPACT_HPP
#define NEXTREACTIONMETHODCOMPACT_HPP
#include <iostream>
#include <climits>
#include "../include/SSA.hpp"
#include "../include/HeapNode.hpp"
#include "../include/IndexedPrioQueue.hpp"
#include "../include/List.hpp"

using namespace std;

class NextReactionMethodCompact : public SSA
{
public:
    virtual void perform(string filename, double simulTime, double beginTime, long int seed);
    virtual ~NextReactionMethodCompact();

protected:
    virtual void initialization(string filename, double simulTime, long int seed);
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
