#ifndef DELAYHASH_HPP
#define DELAYHASH_HPP

#include <iostream>
#include "RingBuffer.hpp"
#include <vector>
using namespace std;

class DelayHash
{

  private:
    int capacity;
    int inUse;
    int firstIndex;
    int firstDelay;
    double precision;
    double low;
    double high;
    RingBuffer **array;
    int hashingFunction(double delayTime);
  public:
    DelayHash(int capacity, double low, double high, double precision);
    ~DelayHash();
    void insertKey(int specIndex, int reacIndex, double delayTime);
    void print();
    bool isEmpty();
    DelayNode* getMinNode();
    vector<DelayNode*> extractEqual(double value);
};

#endif