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
    HeapNode* getMin();
    void insertKey(int index, double time);
    HeapNode* getNode(int index);
    void printQueue();

  private:
    void swap(int ix, int iy);
    void minHeapify(int i);
    void updateAux(int aux);
    int left(int i);
    int right(int i);
    int parent(int i);
    int capacity;
    int heapsize;
    HeapNode **heapArray;
    int *indexArray;
};
#endif
