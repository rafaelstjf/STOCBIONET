#ifndef DEPENDENCYGRAPH_HPP
#define DEPENDENCYGRAPH_HPP

#include <iostream>
#include "DGVertex.hpp"
#include "../Model.hpp"
using namespace std;
class DependencyGraph
{
public:
  DependencyGraph();
  DependencyGraph(double selfEdges,Model* model);
  int *getDependencies(int id);
  void printGraph();
  void createGraph(double selfEdges, Model* model);
  int getDependenciesSize(int id);
  ~DependencyGraph();

protected:
  double selfEdges;
  int numReactions; //size of the vector
  int numSpecies;
  DGVertex **vertex;
  void insertDependency(int id, int val);
  int *unionSet(int **reactants, int **products, double** delay, int reacIndex);      //receives the reactants and products matrix and the
                                                                      //index of the reaction and return the union array
  int *intersectionSet(int *affects, int **reactants, int reacIndex); //receives the reactants and products matrix and the
                                                                      //index of the reaction and return the intersection array
};

#endif // DEPENDENCYGRAPH_H
