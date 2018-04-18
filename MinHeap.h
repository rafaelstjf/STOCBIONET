#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
using namespace std;

class MinHeap
{
  private:

  public:
  MinHeap(int capacity);
  double getMini();
  double extractMin();
  void decreaseKey();
  void insert();
  void delete();
};
#endif