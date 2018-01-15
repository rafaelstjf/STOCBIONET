#ifndef REACTION_H
#define REACTION_H

#include <iostream>
#include <string>
#include <list>
#include "SpecieQuantity.h"
using namespace std;

class Reaction
{
  private:
    string name;
    string textRepresentation;
    double rate;
    list<SpecieQuantity> reactants;
    list<SpecieQuantity> products;
    public:
    Reaction();
    ~Reaction();
    string getName();
    void setName(string name);
    string getTextRepresentation();
    void setTextRepresentation(string textRepresentation);
    double getRate();
    void setRate(double rate);
};
#endif