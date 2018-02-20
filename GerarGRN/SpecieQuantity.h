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
    Specie* specie;
    Delay* delay;

  public:
    SpecieQuantity();
    ~SpecieQuantity();
    int getQuantity();
    void setQuantity(int quant);
    Specie* getSpecie();
    void setSpecie(Specie* sp);
    Delay* getDelay();
    void setDelay(Delay* del);
};
#endif
