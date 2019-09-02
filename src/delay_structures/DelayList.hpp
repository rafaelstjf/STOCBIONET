#ifndef DELAYLIST_HPP
#define DELAYLIST_HPP

#include <iostream>
#include <vector>
#include <climits>
#include "../DelayStructure.hpp"
#include "DelayNode.hpp"
using namespace std;
class DelayList : public DelayStructure
{
private:
  vector<DelayNode *> array;

public:
  DelayList();
  void insertKey(int specIndex, int reacIndex, double delayTime);
  void removeByIndex(int arrayIndex);
  void removeByIndexRange(int arrayIndexBeg, int arrayIndexEnd);
  void print();
  int getArraySize();
  vector<DelayNode *> extractEqualFirst();
  DelayNode *getNode(int index);
  DelayNode *getMinNode();
  ~DelayList();

private:
  int inUse;
};

#endif