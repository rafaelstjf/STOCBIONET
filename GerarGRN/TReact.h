#ifndef TREACT_H
#define TREACT_H

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "SpecieQuantity.h"
#include "Reaction.h"
#include "StringManager.h"

using namespace std;
namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}
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
    void getSpecialNewLines(vector<string> newLines, string lineOrig);
    // void getLinesModulus(vector<string> newLines, string lineOrig);
    void getLines(vector<string> newLines, string lineOrig);
    string getLineSum2(string lineOrig);
    string getLineSum(string lineOrig);
    Reaction getTranslatedReaction(string textReact);
    vector<SpecieQuantity> getListOfSpeciesQuantity(string speciesQuantityText);
    SpecieQuantity getSpecieQuantity(string specQText);
public:
    TReact();
    ~TReact();
    vector<Reaction> getReactions(string textToTranslate, map<string, long int> speciesAndNumbers,map<string, long int> speciesQuantity, vector<string> modelRepresentation);


};
#endif
