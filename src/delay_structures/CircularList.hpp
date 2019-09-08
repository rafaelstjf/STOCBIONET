#ifndef CIRCULARLIST_HPP
#define CIRCULARLIST_HPP

#include <iostream>
#include <cmath>
#include <climits>
#include "DelayNode.hpp"
#include "../DelayStructure.hpp"
#include <vector>
using namespace std;
class CircularList : public DelayStructure
{
public:
  CircularList(int capacity);
  ~CircularList();
  void insertKey(int specIndex, int reacIndex, double delayTime);
  void print();
  vector<DelayNode *> extractEqualFirst();
  DelayNode *getNode(int index);
  DelayNode *getMinNode();
  void removeByIndexRange(vector<int> indexes);
  //
  bool isEmpty();
  int getFirstIndex();
  int getLastIndex();
  int getCapacity();
  void removeByIndex(int index);
  //void removeByIndexRange(int index);
  void removeFirst();

private:
  DelayNode **array;
  int inUse;
  int capacity;
  int first;
  int last;
};
#endif