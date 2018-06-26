#ifndef DEPENDENCYGRAPHNRM_HPP
#define DEPENDENCYGRAPHNRM_HPP

#include <iostream>
#include "../include/DGVertex.hpp"
#include "../include/DependencyGraph.hpp"
using namespace std;
class DependencyGraphNRM : public DependencyGraph
{
public:
    DependencyGraphNRM(int numReactions, int** reactants, int** products, int numSpecies);
    virtual ~DependencyGraphNRM();
    virtual void createGraph(int numReactions, int **reactants, int **products, int numSpecies);
protected:

};

#endif // DEPENDENCYGRAPH_H
