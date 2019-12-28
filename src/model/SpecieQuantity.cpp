#include "SpecieQuantity.hpp"

SpecieQuantity::SpecieQuantity(){
quantity = 0;

}
SpecieQuantity::~SpecieQuantity(){
}
double SpecieQuantity::getQuantity(){
    return quantity;
}
void SpecieQuantity::setQuantity(double quant){
    quantity = quant;
}
Delay* SpecieQuantity::getDelay(){
    return delay;
}
Specie* SpecieQuantity::getSpecie(){
    return specie;
}
void SpecieQuantity::setSpecie(Specie* sp){
   specie = sp;
}
void SpecieQuantity::setDelay(Delay* de){
    delay = de;
}
