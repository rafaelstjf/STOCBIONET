#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <iostream>
#include <cmath>
#include <climits>
#include "DelayNode.hpp"
#include "../DelayStructure.hpp"
#include <vector>
using namespace std;
class RingBuffer : public DelayStructure
{
public:
  RingBuffer(int capacity);
  ~RingBuffer();
  void insertKey(int specIndex, int reacIndex, double delayTime);
  void print();
  vector<DelayNode *> extractEqual(double value);
  DelayNode *getNode(int index);
  DelayNode *getMinNode();
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