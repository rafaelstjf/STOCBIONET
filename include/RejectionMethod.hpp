#ifndef REJECTIONMETHOD_HPP
#define REJECTIONMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"
#include "../include/Dependency_Graph/DelayedDependencyGraph.hpp"
#include "../include/delay_structures/DelayList.hpp"
#include "../include/delay_structures/DelayNode.hpp"
#include "../include/delay_structures/DelayHash.hpp"
#include "../include/delay_structures/RingBuffer.hpp"

using namespace std;

class RejectionMethod : public SSA
{
public:
    void perform(Model* model, double maximumTime, double initialTime, long int seed);
    virtual ~RejectionMethod();

protected:
    virtual void initialization(Model* model, double maximumTime, double initialTime, long int seed);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    virtual void updateSpeciesQuantities(int index);
    //DelayList* list;
    DelayHash* delayStructure;
    DelayedDependencyGraph* ddg;

private:

};

#endif