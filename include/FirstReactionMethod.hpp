#ifndef FIRSTREACTIONMETHOD_HPP
#define FIRSTREACTIONMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"

using namespace std;

class FirstReactionMethod : public SSA
{
public:
  virtual void perform(Model* model, double maximumTime, double initialTime, long int seed);
  virtual ~FirstReactionMethod();

protected:
  double *t;
  virtual void initialization(Model* model, double maximumTime, double initialTime, long int seed); //read the model and initialization data structures
  virtual void reacTimeGeneration();
  virtual void reacSelection();
  virtual void reacExecution();

private:
};

#endif // FIRSTREACTIONMETHOD_H
