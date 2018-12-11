#ifndef DELAYNODE_HPP
#define DELAYNODE_HPP

#include <iostream>
using namespace std;

class DelayNode
{
  private:
    double delayTime;
    int specIndex;
    int reacIndex;

  public:
    DelayNode(int specIndex, int reacIndex, double delayTime);
    ~DelayNode();
    void setDelayTime(double delayTime);
    void setSpecIndex(int specIndex);
    void setReacIndex(int reacIndex);
    double getDelayTime();
    int getSpecIndex();
    int getReacIndex();
};
#endif