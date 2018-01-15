#include "SpecieQuantity.h"

SpecieQuantity::SpecieQuantity(){
quantity = 0;
delay = NULL;
specie = NULL;
}
SpecieQuantity::~SpecieQuantity(){
    delete delay;
    delete specie;
}
int SpecieQuantity::getQuantity(){
    return quantity;
}
void SpecieQuantity::setQuantity(int quantity){
    this.quantity = quantity;
}
Delay* SpecieQuantity::getDelay(){
    return delay;
}
Specie* SpecieQuantity::getSpecie(){
    return specie;
}
void SpecieQuantity::setSpecie(Specie* specie){
    this.specie = specie;
}
void SpecieQuantity::setDelay(Delay* delay){
    this.delay = delay;
}