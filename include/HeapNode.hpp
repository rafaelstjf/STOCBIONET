#ifndef HEAPNODE_HPP
#define HEAPNODE_HPP

#include <iostream>
using namespace std;

class HeapNode
{
  private:
    int index;
    double time;

  public:
    HeapNode();
    HeapNode(int index, double time);
    ~HeapNode();
    void setIndex(int index);
    void setTime(double time);
    int getIndex();
    double getTime();
};

#endif