#ifndef DELAY_H
#define DELAY_H

#include <iostream>
using namespace std;
class Delay
{
  private:
    double value;
    double variation;

  public:
    Delay();
    ~Delay();
    void setValue(double val);
    void setVariation(double var);
    double getValue();
    double getVariation();
};
#endif
