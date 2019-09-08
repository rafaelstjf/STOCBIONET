#ifndef DELAYHASH_HPP
#define DELAYHASH_HPP

#include <iostream>
#include "CircularList.hpp"
#include "../DelayStructure.hpp"
#include <vector>
using namespace std;

class DelayHash : public DelayStructure
{

private:
  typedef struct table
  {
    double low;
    double high;
    vector<CircularList *> array;
    int inUse;
  } Table;
  Table *table1;
  Table *table2;
  int capacity;
  int firstIndex;
  double firstDelay;
  int firstTable;
  double precision;
  double lowestDelay;
  double biggestDelay;
  int hashingFunction(double delayTime, double low, double high);

public:
  DelayHash(double **delaysValue, int reacNumber, int specNumber);
  ~DelayHash();
  void insertKey(int specIndex, int reacIndex, double delayTime);
  void print();
  bool isEmpty();
  DelayNode *getMinNode();
  vector<DelayNode *> extractEqualFirst();
};

#endif