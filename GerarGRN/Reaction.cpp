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
void Reaction::setName(string n){
    name = n;
}
void Reaction::setTextRepresentation(string textRep){
    textRepresentation = textRep;
}
double Reaction::getRate(){
    return rate;
}
void Reaction::setRate(double r){
   rate = r;
}
vector<SpecieQuantity*> Reaction::getReactants(){
    return reactants;
}
vector<SpecieQuantity*> Reaction::getProducts(){
    return products;
}
void Reaction::setReactants(vector<SpecieQuantity*> &reac){
    reactants = reac;
}
void Reaction::setProducts(vector<SpecieQuantity*> &prod){
    products = prod;
}
