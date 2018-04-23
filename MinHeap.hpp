#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <iostream>
#include <climits>
using namespace std;

class MinHeap
{
  private:
  double *harr; //poninter to array of elements in heap
  int capacity; //maximum possible size of min heap
  int heapSize; //current number of elements in min heap
  public:
  MinHeap(int capacity);
  void minHeapify(int i);
  int parent(int i);
  int left(int i);
  int right(int i);
  double extractMin();
  void decreaseKey(int i, double newVal);
  double getMini();
  void deleteKey(int i);
  void insertKey(double val);
  
};
#endif