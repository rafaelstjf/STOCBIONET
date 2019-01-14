#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <iostream>
#include <cmath>
#include <climits>
#include "DelayNode.hpp"
#include <vector>
using namespace std;
class RingBuffer
{
public:
  RingBuffer(int capacity);
  ~RingBuffer();
  bool isEmpty();
  void insertKey(int specIndex, int reacIndex, double delayTime);
  void removeFirst();
  void print();
  void removeByIndex(int index);
  int getFirstIndex();
  int getCapacity();
  int getLastIndex();
  DelayNode* getNode(int index);
  vector<DelayNode*>  extractEqual(double value);
  DelayNode* getMinNode();

private:
  DelayNode** array;
  int inUse;
  int capacity;
  int first;
  int last;
};
#endif