#ifndef TREACT_H
#define TREACT_H

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include "SpecieQuantity.h"
#include "Reaction.h"
#include "StringManager.h"
using namespace std;

class TReact
{
  private:
    int reactionCounter;
    map<string, double> constants;
    map<string, long int> speciesNumber;
    int specieCounter;
    bool even;
    StringManager* sm;
    //functions
    void getSpecialNewLines(list<string> newLines, string lineOrig);
   // void getLinesModulus(list<string> newLines, string lineOrig);
    void getLines(list<string> newLines, string lineOrig);
    string getLineSum2(string lineOrig);
    string getLineSum(string lineOrig);
    Reaction* getTranslatedReaction(string textReact); 
    list<SpecieQuantity> getListOfSpeciesQuantity(string speciesQuantityText);
    SpecieQuantity getSpecieQuantity(string specQText);
    string replaceChar(string str, char c1, char c2);
  public:
  TReact();
  ~TReact();
  list<Reaction> getReactions(string textToTranslate, map<string, long int> speciesAndNumbers,map<string, long int> speciesQuantity, list<string> modelRepresentation);


};
#endif