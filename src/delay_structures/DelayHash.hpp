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
  struct Table
  {
    int low;
    int high;
    vector<RingBuffer *> array;
    int inUse;
  };
  Table *table1;
  Table *table2;
  int capacity;
  int firstIndex;
  int firstDelay;
  int firstTable;
  double precision;
  double lowestDelay;
  double biggestDelay;
  int hashingFunction(double delayTime, int low, int high);

public:
  DelayHash(double **delaysValue, int reacNumber, int specNumber);
  ~DelayHash();
  void insertKey(int specIndex, int reacIndex, double delayTime);
  void print();
  bool isEmpty();
  DelayNode *getMinNode();
  vector<DelayNode *> extractEqual(double value);
};

#endif