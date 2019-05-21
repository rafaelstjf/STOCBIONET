#ifndef DELAYSTRUCTURE_HPP
#define DELAYSTRUCTURE_HPP
#include "delay_structures/DelayNode.hpp"
#include <vector>
#include <iostream>

using namespace std;
class DelayStructure
{
private:

protected:

public:
  DelayStructure();
  virtual ~DelayStructure();
  virtual void insertKey(int specIndex, int reacIndex, double delayTime);
  virtual void print();
  virtual vector<DelayNode *> extractEqual(double value);
  virtual DelayNode *getNode(int index);
  virtual DelayNode *getMinNode();
};
#endif