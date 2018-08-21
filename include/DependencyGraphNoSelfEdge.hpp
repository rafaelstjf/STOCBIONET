#ifndef DEPENDENCYGRAPHNOSELFEDGE_HPP
#define DEPENDENCYGRAPHNOSELFEDGE_HPP

#include <iostream>
#include "../include/DGVertex.hpp"
#include "../include/DependencyGraph.hpp"
using namespace std;
class DependencyGraphNoSelfEdge : public DependencyGraph
{
public:
    DependencyGraphNoSelfEdge(int numReactions, int** reactants, int** products, int numSpecies);
    virtual ~DependencyGraphNoSelfEdge();
    virtual void createGraph(int numReactions, int **reactants, int **products, int numSpecies);
protected:

};

#endif // DEPENDENCYGRAPH_H
