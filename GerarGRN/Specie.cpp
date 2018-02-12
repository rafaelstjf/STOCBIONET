#include "Specie.h"

Specie::Specie(){
    number = 0;
    name = '\0';
}
Specie::~Specie(){

}
void Specie::setName(string n){
  name = n;
}
void Specie::setNumber(long int num){
   number = num;
}
string Specie::getName(){
    return name;
}
long int Specie::getNumber(){
    return number;
}
