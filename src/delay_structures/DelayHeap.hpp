#ifndef DELAYHEAP_HPP
#define DELAYHEAP_HPP

#include <iostream>
#include <climits>
#include "DelayNode.hpp"
#include "../DelayStructure.hpp"
#include <vector>
#include <cmath>
using namespace std;

class DelayHeap : public DelayStructure
{

private:
  int capacity;
  int heapSize;
  DelayNode **array;
  void minHeapify(int a);
  int parent(int i);
  int left(int i);
  int right(int i);
  DelayNode *extractMin();
  void deleteKey(int key);
  void decreaseKey(int i, int specIndex, double delayTime, int reacIndex);
  void swap(DelayNode *a, DelayNode *b);

public:
  DelayHeap(int capacity);
  void insertKey(int specIndex, int reacIndex, double delayTime);
  void print();
  bool isHeap();
  DelayNode* getMinNode();
  vector<DelayNode *> extractEqual(double value);
  ~DelayHeap();

};
#endif