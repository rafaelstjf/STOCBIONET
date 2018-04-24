#ifndef SPECIEQUANTITIY_HPP
#define SPECIEQUANTITIY_HPP

#include <iostream>
#include "Specie.hpp"
#include "Delay.hpp"

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
