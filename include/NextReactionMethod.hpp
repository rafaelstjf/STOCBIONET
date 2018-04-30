#ifndef NEXTREACTIONMETHOD_HPP
#define NEXTREACTIONMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"

using namespace std;

class NextReactionMethod : public SSA
{
  public:
  void peform(string filename, double simulTime);
  virtual ~NextReactionMethod();
  private:
  void initialization(string filename, double simulTime);
  void calcPropensity();
  void printResult();
  void saveToFile();

};
#endif