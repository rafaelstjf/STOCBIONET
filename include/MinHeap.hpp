#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <iostream>
#include <climits>
#include "../include/HeapNode.hpp"
using namespace std;

class MinHeap
{
  private:
  HeapNode *harr; //pointer to array of elements in heap
  int capacity; //maximum possible size of min heap
  int heapSize; //current number of elements in min heap
  public:
  MinHeap(int capacity);
  void minHeapify(int i);
  int parent(int i);
  int left(int i);
  int right(int i);
  HeapNode* extractMin();
  void decreaseKey(int i, double newTime, int newIndex);
  double getMini();
  void deleteKey(int i);
  void insertKey(int index, double t);
  
};
#endif