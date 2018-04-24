#ifndef DEPENDENCYGRAPH_HPP
#define DEPENDENCYGRAPH_HPP

#include <iostream>
#include "../include/DGVertex.hpp"
using namespace std;
class DependencyGraph
{
public:
    DependencyGraph(int numReactions, int** reactants, int** products, int numSpecies);
    int* getDependencies(int id);
    void insertDependency(int id, int val);
    void printGraph();
    int getDependenciesSize(int id);
    virtual ~DependencyGraph();

private:
    int numReactions; //size of the vector
    int numSpecies;
    DGVertex** vertex;
    int* unionSet(int* a, int* b);
    int* intersectionSet(int* a, int*b);

};

#endif // DEPENDENCYGRAPH_H
