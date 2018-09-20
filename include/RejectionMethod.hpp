#ifndef REJECTIONMETHOD_HPP
#define REJECTIONMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"
#include "../include/DelayList.hpp"
#include "../include/HeapNode.hpp"
using namespace std;

class RejectionMethod : public SSA
{
public:
    void perform(string filename, double simulTime, double beginTime, long int seed);
    virtual ~RejectionMethod();

protected:
    virtual void initialization(string filename, double simultime, long int seed);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    virtual void updateSpeciesQuantities(int index);
    DelayList* list;

private:

};

#endif