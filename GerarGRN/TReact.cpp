#include "TReact.h"
TReact::TReact()
{
    reactionCounter = 0;
    specieCounter = 0;
    even = false;
    sm = new StringManager();
}
TReact::~TReact()
{
    delete sm;
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
    textToTranslate = sm->replaceString(textToTranslate, "\r\n", "");
    textToTranslate = sm->replaceString(textToTranslate, "\n", "");
    vector<string> lines = sm->explode(TextToTranslate, ';');
    for (i = 0; i < lines.size(); i++)
    {
        newLines.clear();
        newLinesX.clear();
    }
}
void TReact::getLines(list<string> newLines, string lineOrig)
{
    size_t found;
    found = lineOrig.find("[...]");
    if (found != string::npos)
        return; //string found
    found = lineOrig.find("[");
    if (found != string::npos)
    { //string found
        int idxStart = lineOrig.find("[") + 1;
        int idxEnd = lineOrig.find("]");
        string key = lineOrig.substr(idxStart, idxEnd - idxStart);
        string keyOri = "";
        string plus = "";
        if (key.find("+") != string::npos)
        {
            vector<string> valK = sm->explode(key, '+');
            keyOri = valK[0];
            key = keyOri;
            plis = valK[1];
            int n;
            //trying to parse
            istringstream iss(valK[0]);
            iss >> n;
            int m;
            istringstream iss2(valK[1]);
            iss2 >> m;
            string tempString = ("[" + to_string(n) + to_string(m) + "]");
            lineOrig = sm->replaceString(tempString, to_string(n + m));
            //                            newLines.Add(GetLineSum2(lineOrig));
        }
    }
}
string TReact::getLineSum2(string lineOrig)
{
    if (lineOrig.found("[") != string::npos)
    {
        int idxStart = lineOrig.find("[") + 1;
        int idxEnd = lineOrig.find("]");
        string key = lineOrig.substr(idxStart, idxEnd - idxStart);
        string keyOri = "";
        string plus = "";
        if (key.find("+") != string::npos)
        {
            vector<string> valK = sm->explode(key, '+');
            keyOri = valK[0];
            key = keyOri;
            plus = valK[1];
            int n;
            istringstream iss(valK[0]);
            iss > n;
            int m;
            istringstream iss2(valK[1]);
            iss2 >> m;
            return(sm->replaceString(tempString, to_string(n + m)));

        }
    }
    return lineOrig;
}
string TReact::getLineSum(string lineOrig){
    if(lineOrig.find("{") != string::npos){
        int idxStart = lineOrig.find("{") + 1;
        int idxEnd = lineOrig.find("}");
        string key = lineOrig.substr(idxStart, idxEnd - idxStart);
        string keyOri = "";
        string plus= "";
        if(key.find("+") != string::npos){
            vector<string> valK = sm->explode(key, '+');
            keyOri = valK[0];
            key = keyOri;
            plus = valK[1];
            int n;
            istringstream iss(valK[0]);
            iss > n;
            int m;
            istringstream iss2(valK[1]);
            iss2 >> m;
            return(sm->replaceString(tempString, to_string(n + m)));
        } 
        return lineOrig;
    }
}
Reaction* TReact::getTranslatedReaction(string textReact){
    Reaction* react = new Reaction();
    vector<string> reactionSplit;
    textReact = 
}
