#ifndef DEPENDENCYGRAPH_HPP
#define DEPENDENCYGRAPH_HPP

#include <iostream>
#include "../include/DGVertex.hpp"
using namespace std;
class DependencyGraph
{
public:
  DependencyGraph();
  DependencyGraph(double selfEdges, int **reactants, int **products, int numReactions, int numSpecies);
  int *getDependencies(int id);
  void printGraph();
  void createGraph(double selfEdges, int **reactants, int **products, int numReactions, int numSpecies);
  int getDependenciesSize(int id);
  ~DependencyGraph();

protected:
  double selfEdges;
  int numReactions; //size of the vector
  int numSpecies;
  DGVertex **vertex;
  void insertDependency(int id, int val);
  int *unionSet(int **reactants, int **products, int reacIndex);      //receives the reactants and products matrix and the
                                                                      //index of the reaction and return the union array
  int *intersectionSet(int *affects, int **reactants, int reacIndex); //receives the reactants and products matrix and the
                                                                      //index of the reaction and return the intersection array
};

#endif // DEPENDENCYGRAPH_H
