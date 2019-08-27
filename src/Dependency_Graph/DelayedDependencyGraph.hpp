#ifndef DELAYEDDEPENDENCYGRAHP_HPP
#define DELAYEDDEPENDENCYGRAHP_HPP

#include "DGVertex.hpp"
#include <iostream>
using namespace std;

class DelayedDependencyGraph
{
public:
  DelayedDependencyGraph();
  DelayedDependencyGraph(int reacNumber, int specNumber, int **reactants);
  void createGraph(int reacNumber, int specNumber, int **reactants);
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