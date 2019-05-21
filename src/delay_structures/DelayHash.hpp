#ifndef DELAYHASH_HPP
#define DELAYHASH_HPP

#include <iostream>
#include "RingBuffer.hpp"
#include "../DelayStructure.hpp"
#include <vector>
using namespace std;

class DelayHash : public DelayStructure
{

  private:
    int capacity;
    int inUse;
    int firstIndex;
    int firstDelay;
    double precision;
    double low;
    double high;
    double lowestDelay;
    double biggestDelay;
    RingBuffer **array;
    int hashingFunction(double delayTime);
  public:
    DelayHash(int capacity, double low, double high, double precision, double** delaysValue, int reacNumber, int specNumber);
    ~DelayHash();
    void insertKey(int specIndex, int reacIndex, double delayTime);
    void print();
    bool isEmpty();
    DelayNode* getMinNode();
    vector<DelayNode*> extractEqual(double value);
};

#endif