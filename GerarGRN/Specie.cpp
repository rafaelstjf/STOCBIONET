#include "Specie.h"

Specie::Specie(){
    number = 0;
    name = '\0';
}
Specie::~Specie(){

}
void Specie::setName(string name){
    this.name = name;
}
void Specie::setNumber(long int number){
    this.number = number;
}
string Specie::getName(){
    return name;
}
long int Specie::getNumber(){
    return number;
}
