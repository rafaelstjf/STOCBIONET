#ifndef SPECIEQUANTITIY_H
#define SPECIEQUANTITIY_H

#include <iostream>
#include "Specie.h"
#include "Delay.h"

using namespace std;
class SpecieQuantity
{
  private:
    int quantity;
    Specie *specie;
    Delay *delay;

  public:
    SpecieQuantity();
    ~SpecieQuantity();
    int getQuantity();
    void setQuantity(int quantity);
    Specie *getSpecie();
    void SetSpecie(Specie *specie);
    Delay *getDelay();
    void setDelay(Delay *delay);
};
#endif