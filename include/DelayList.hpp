#ifndef DELAYLIST_HPP
#define DELAYLIST_HPP

#include <iostream>
#include <vector>
using namespace std;
class DelayList
{
private:
  struct Node
  {
    int specIndex;
    double delayTime;
    int reacIndex;
  };
  vector<Node> array;

public:
  DelayList();
  void insert(int specIndex, int reacIndex, double delayTime);
  void removeBySpecie(int specIndex);
  void removeByArrayIndex(int arrayIndex);
  void sortList();
  double getDelayTime(int index);
  int getSpecIndex(int index);
  int getReacIndex(int index);
  int getArraySize();
  ~DelayList();
};

#endif