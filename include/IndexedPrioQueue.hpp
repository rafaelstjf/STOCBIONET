#ifndef INDEXEDPRIOQUEUE_HPP
#define INDEXEDPRIOQUEUE_HPP

#include "../include/HeapNode.hpp"
#include <iostream>
using namespace std;

class IndexedPrioQueue
{
  public:
    IndexedPrioQueue(int capacity);
    ~IndexedPrioQueue();
    void update(int index, double time);

  private:
    void swap(HeapNode* x, HeapNode* y, int ix, int iy);
    void minHeapify(int i);
    void updateAux(int aux);
    int left(int i);
    int right(int i);
    int parent(int i);
    void insertKey(int index, double time);
    HeapNode* getMin();
    int capacity;
    int heapsize;
    HeapNode *heapArray;
    int *indexArray;
};
#endif