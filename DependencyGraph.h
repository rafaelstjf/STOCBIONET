#ifndef DEPENDENCYGRAPH_H
#define DEPENDENCYGRAPH_H

#include <iostream>
#include "DGVertex.h"
#include <sbml/SBMLTypes.h> //sbml external library
#include <sbml/common/extern.h>

using namespace std;
class DependencyGraph
{
public:
    DependencyGraph(int n, int** r, int** p, int numElements);
    int* getDependencies(int id);
    void insertDependency(int id, int val);
    void printGraph();
    int* getDependenciesSize(int id);
    void tests(int op);
    virtual ~DependencyGraph();

private:
    int n; //size of the vector
    int numElements;
    DGVertex** vertex;
    int* unionSet(int* a, int* b);
    int* intersectionSet(int* a, int*b);
    int* extractElements(int** a, int c);

};

#endif // DEPENDENCYGRAPH_H
