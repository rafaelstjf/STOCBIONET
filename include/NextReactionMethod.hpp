#ifndef NEXTREACTIONMETHOD_HPP
#define NEXTREACTIONMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"
#include "../include/MinHeap.hpp"

using namespace std;

class NextReactionMethod : public SSA
{
  public:
  void peform(string filename, double simulTime);
  virtual ~NextReactionMethod();
  private:
  void initialize(string filename, double simulTime);
  void calcPropensity();
  void printResult();
  void saveToFile();

};
#endif