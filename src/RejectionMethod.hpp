#ifndef REJECTIONMETHOD_HPP
#define REJECTIONMETHOD_HPP

#include <iostream>
#include "SSA.hpp"
#include "Dependency_Graph/DelayedDependencyGraph.hpp"
#include "delay_structures/DelayList.hpp"
#include "delay_structures/DelayNode.hpp"
#include "delay_structures/DelayHash.hpp"
#include "delay_structures/DelayHeap.hpp"
#include "delay_structures/CircularList.hpp"
#include "DelayStructure.hpp"
using namespace std;

class RejectionMethod : public SSA
{
public:
    void perform(Model* model, double maximumTime, double initialTime, long int seed);
    void setDelayStructure(int op);
    virtual ~RejectionMethod();

protected:
    virtual void initialization(Model* model, double maximumTime, double initialTime, long int seed);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    virtual void updateSpeciesQuantities(int index);
    DelayStructure* delayStructure;
    DelayedDependencyGraph* ddg;

private:
    int structOp;
    void chooseStructure();
};

#endif