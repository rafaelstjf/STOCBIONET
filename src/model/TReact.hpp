#ifndef TREACT_HPP
#define TREACT_HPP

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "SpecieQuantity.hpp"
#include "Reaction.hpp"
#include "StringManager.hpp"

using namespace std;

class TReact
{
private:
    int reactionCounter;
    map<string, double> constants;
    map<string, long int> speciesNumber;
    int specieCounter;
    bool even;
    bool debug;
    StringManager* sm;
    //functions
    void getSpecialNewLines(vector<string>& newLines, string lineOrig);
    // void getLinesModulus(vector<string> newLines, string lineOrig);
    void getLines(vector<string>& newLines, string lineOrig);
    string getLineSum2(string lineOrig);
    string getLineSum(string lineOrig);
    Reaction* getTranslatedReaction(string textReact);
    vector<SpecieQuantity*> getListOfSpeciesQuantity(string speciesQuantityText);
    SpecieQuantity* getSpecieQuantity(string specQText);
public:
    TReact(bool debug);
    ~TReact();
    vector<Reaction*> getReactions(string textToTranslate, map<string, long int>& speciesAndNumbers,map<string, long int>& speciesQuantity, vector<string>& modelRepresentation);


};
#endif
