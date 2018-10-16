#ifndef DELAYEDDEPENDENCYGRAHP_HPP
#define DELAYEDDEPENDENCYGRAHP_HPP

#include "../include/DGVertex.hpp"
#include <iostream>
using namespace std;

class DelayedDependencyGraph
{
  public:
    DelayedDependencyGraph();
    DelayedDependencyGraph(int **reactants, int **products, int numReactions, int numSpecies);
    void createGraph(int **reactants, int **products, int numReactions, int numSpecies);
    int *getDependencies(int id);
    int getDependenciesSize(int id);
    void printGraph();
    ~DelayedDependencyGraph();

  private:
    int numSpecies; //size of the vector
    int numReactions;
    DGVertex **vertex;
    void insertDependency(int id, int val);
};
#endif