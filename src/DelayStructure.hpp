#ifndef DELAYSTRUCTURE_HPP
#define DELAYSTRUCTURE_HPP
#include "delay_structures/DelayNode.hpp"
#include <vector>
#include <iostream>
#define INF 1.0E9
#define EP 1.0E-5
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