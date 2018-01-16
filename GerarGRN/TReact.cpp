#include "TReact.h"
TReact::TReact()
{
    reactionCounter = 0;
    specieCounter = 0;
    even = false;
}
TReact::~TReact()
{
}
list<Reaction> TReact::getReactions(string textToTranslate, map<string, long int> speciesAndNumbers, map<string, long int> speciesQuantity, list<string> modelRepresentation)
{
    Reaction react;
    list<Reaction> ret;
    list<string> newLinesX;
    list<string> newLines;
    list<string> modelRepresentation;
    string con;
    constants.clear();
    reactionCounter = 0;
    specieCounter = 0;
    //textToTranslate = 
}