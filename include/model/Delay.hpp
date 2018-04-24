#ifndef DELAY_HPP
#define DELAY_HPP

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
