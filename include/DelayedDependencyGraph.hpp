#ifndef DELAYEDDEPENDENCYGRAHP_HPP
#define DELAYEDDEPENDENCYGRAHP_HPP

#include "../include/DGVertex.hpp"
#include "../include/Model.hpp"
#include <iostream>
using namespace std;

class DelayedDependencyGraph
{
  public:
    DelayedDependencyGraph();
    DelayedDependencyGraph(Model* model);
    void createGraph(Model* model);
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