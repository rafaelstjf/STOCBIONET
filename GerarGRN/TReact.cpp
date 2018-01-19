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
string TReact::replaceChar(string str, char c1, char c2){
    for(int i = 0; i<str.length(); i++){
        if(str[i]==c1)
            str[i] = c2;
    }
    return string;
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
    textToTranslate = 
}