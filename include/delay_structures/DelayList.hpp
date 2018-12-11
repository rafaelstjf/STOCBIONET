#ifndef DELAYLIST_HPP
#define DELAYLIST_HPP

#include <iostream>
#include <vector>
#include "DelayNode.hpp"
using namespace std;
class DelayList
{
private:
  vector<DelayNode *> array;

public:
  DelayList();
  void insertKey(int specIndex, int reacIndex, double delayTime);
  void removeByIndex(int arrayIndex);
  void print();
  int getArraySize();
  vector<DelayNode *> extractEqual(double value);
  DelayNode *getNode(int index);
  DelayNode *getMinNode();
  ~DelayList();

private:
  void sortList();
};

#endif