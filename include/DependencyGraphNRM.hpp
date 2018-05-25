#ifndef DEPENDENCYGRAPH_HPP
#define DEPENDENCYGRAPH_HPP

#include <iostream>
#include "../include/DGVertex.hpp"
using namespace std;
class DependencyGraph : public DependencyGraph
{
public:
    DependencyGraph(int numReactions, int** reactants, int** products, int numSpecies);
    int* getDependencies(int id);
    virtual void insertDependency(int id, int val);
    virtual void printGraph();
    virtual int getDependenciesSize(int id);
    virtual ~DependencyGraph();

protected:
    virtual int* unionSet(int* a, int* b);
    virtual int* intersectionSet(int* a, int*b);

};

#endif // DEPENDENCYGRAPH_H
