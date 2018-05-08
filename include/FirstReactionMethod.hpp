#ifndef FIRSTREACTIONMETHOD_HPP
#define FIRSTREACTIONMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"

using namespace std;

class FirstReactionMethod : public SSA
{
public:
  virtual void perform(string filename, double simulTime);
  virtual ~FirstReactionMethod();

protected:
  double *t;
  virtual void initialization(string filename, double simulTime); //read the model and initialization data structures
  virtual void calcPropensity();                                  //calculate the propensity function for all the reactions
  virtual void printResult();
  virtual void calcPropOne(int index);
  virtual void reacTimeGeneration();
  virtual void reacSelection();
  virtual void reacExecution();

private:
};

#endif // FIRSTREACTIONMETHOD_H
