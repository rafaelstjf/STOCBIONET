#include "Reaction.h"

Reaction::Reaction(){
    name = '\0';
    textRepresentation = '\0';
    rate  = 0.0;
    reactants.clear();
    products.clear();
}
Reaction::~Reaction(){

}
string Reaction::getName(){
    return name;
}
string Reaction::getTextRepresentation(){
    return textRepresentation;
}
void Reaction::setName(string name){
    this.name = name;
}
void Reaction::setTextRepresentation(string textRepresentation){
    this.textRepresentation = textRepresentation;
}
double Reaction::getRate(){
    return rate;
}
void Reaction::setRate(double rate){
    this.rate = rate;
}
list<SpecieQuantity> Reaction::getReactants(){
    return reactants;
}
list<SpecieQuantity> Reaction::getProducts(){
    return products;
}
void Reaction::setReactants(list<SpecieQuantity> reactants){
    this.reactants = reactants;
}
void Reaction::setProducts(list<SpecieQuantity> products){
    this.products = products;
}
