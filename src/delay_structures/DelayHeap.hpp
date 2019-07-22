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
  void minHeapify(int a); //to heapify a subtree with the root at given index
  int parent(int i);
  int left(int i);
  int right(int i);
  DelayNode *extractMin(); //it removes the minimum element from MinHeap
  void deleteKey(int key);
  void decreaseKey(int i, int specIndex, double delayTime, int reacIndex);

public:
  DelayHeap(int capacity);
  void insertKey(int specIndex, int reacIndex, double delayTime);//It adds a new key at the end of the tree. IF new key is greater than its parent, then the algorithm doesn’t need to do anything. Otherwise, it needs to traverse up to fix the violated heap property
  void print(); //it prints the heap
  bool isHeap(); //it checks if the heap is correctly build
  DelayNode* getMinNode(); //It returns the root element of Min Heap
  vector<DelayNode *> extractEqualFirst(); //It extracts all the elements that are equal to the first
  ~DelayHeap();

};
#endif