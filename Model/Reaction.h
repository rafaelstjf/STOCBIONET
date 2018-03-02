#ifndef REACTION_H
#define REACTION_H

#include <iostream>
#include <string>
#include <vector>
#include "SpecieQuantity.h"
using namespace std;

class Reaction
{
  private:
    string name;
    string textRepresentation;
    double rate;
    vector<SpecieQuantity*> reactants;
    vector<SpecieQuantity*> products;
    public:
    Reaction();
    ~Reaction();
    string getName();
    void setName(string n);
    string getTextRepresentation();
    void setTextRepresentation(string textRep);
    double getRate();
    void setRate(double r);
    vector<SpecieQuantity*> getReactants();
    vector<SpecieQuantity*> getProducts();
    void setReactants(vector<SpecieQuantity*> &reac);
    void setProducts(vector<SpecieQuantity*> &prod);
};
#endif
