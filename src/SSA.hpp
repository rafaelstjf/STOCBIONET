#ifndef SSA_HPP
#define SSA_HPP

#include <string>
#include <iostream>
#include <stdlib.h>
#include <climits>
#include <map>
#include "Model.hpp"
#include "Dependency_Graph/DependencyGraph.hpp"
#include "Utils.hpp"
#include "Log/Log.hpp"

#define INF 1.0E9
#define EP 1.0E-5
using namespace std;

class SSA
{
public:
  virtual void perform(Model *model, double maximumTime, double initialTime, long int seed) = 0;
  virtual bool checkSucess();
  virtual ~SSA();
  virtual void printResult();
  virtual void saveToFile();
  virtual void saveDetailsToFile();
  virtual void onBatch();
  virtual Log *getLog();
  unsigned long int getSeed();
  double getReacPerSecond();
  double getNumberReacExecuted();
  double getTimeSpent();

protected:
  bool batch = false;;
  Utils *ut;
  Log *log;
  DependencyGraph *dg;
  Model *model;
  double totalPropensity; //sum of all the propensities
  long double currentTime;     //current time of the simulation
  double initialTime;     //time that the simulation begins
  int selectedReaction;
  double maximumTime; //simulation time
  string methodOutName;
  double *propArray;    //propensity array
  int *specQuantity;    //species quantity
  double reacPerSecond; //number of reactions executed per second
  int reacCount;        //number of reactions executed in a simulation
  bool sucess;          //boolean variable used to check if the simulation was performed

  //functions
  virtual void initialization(Model *model, double maximumTime, double initialTime, long int seed); //read the model and initialization data structures
  virtual void calcPropensity();                                                                    //calculate the propensity function for each reaction
  virtual void calcPropOne(int index);
  virtual void reacTimeGeneration() = 0;
  virtual void reacSelection() = 0;
  virtual void reacExecution() = 0;
  virtual void updateSpeciesQuantities(int index);
  virtual void postSimulation(double totalTime);
};

#endif // SSA_H
