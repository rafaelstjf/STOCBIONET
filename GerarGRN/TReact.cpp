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
    string x;
    Reaction react;
    list<Reaction> ret;
    list<string> newLinesX;
    list<string> newLines;
    list<string> modelRepresentation;
    vector<string> con;
    constants.clear();
    reactionCounter = 0;
    specieCounter = 0;
    textToTranslate = sm->replaceString(textToTranslate, "\r\n", "");
    textToTranslate = sm->replaceString(textToTranslate, "\n", "");
    vector<string> lines = sm->explode(TextToTranslate, ';');
    for (i = 0; i < lines.size(); i++)
    {
        x = lines[i];
        newLines.clear();
        newLinesX.clear();
        getLines(newLinesX, lineOrig);
        for (int j = 0; j < newLinesX.size(); j++)
        {
            string y = sm - replaceChar(x, '{', ']');
            y = sm->replaceChar(y, '}', ']');
            getLines(newlines, y);
        }
        for (int j = 0; j < newLines.size(); j++)
        {
            string line = newLines[j];
            if (sm->trim(line).size() > 0)
            {
                if (line.find('>') != string::npos)
                {
                    react = getTranslatedReaction(line);
                    if (react != NULL)
                    {
                        ret.add(react);
                    }
                    modelRepresentation.add(sm->trim(line));
                }
                else
                {
                    con = sm->explode(line, '=');
                    if (con.size() != 2)
                    {
                        cout << "Invalid constant " << line << endl;
                    }
                    else if (constants.find(con[0]) != map::end)
                    {
                        cout << "Duplicate constant" << line << endl;
                    }
                    else
                    {
                        constants.insert(make_pair(con[0], stoi(sm->replaceChar(con[1], '.', ','))));
                        modelRepresentation.add(sm->trim(line));
                    }
                }
            }
        }
    }
    speciesAndNumbers = speciesNumber;
    map<string, long int> speciesQuantity;
    map<string, long int>::iterator it = speciesAndNumbers.begin();
    while (it != speciesAndNumbers.end())
    {
        if (constants.count(it->first) > 0)
        {
            speciesQuantity.insert(make_pair(it->first, constants[constants.count(it->first)]->second))
        }
        else
        {

            SpecieQuantity.insert(make_pair(it->first, 0));
        }
    }
    return ret;
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
            string tempString = ("[" + to_string(n) + "+" + to_string(m) + "]");
            lineOrig = sm->replaceString(tempString, to_string(n + m));
            newLines.insert(GetLineSum2(lineOrig));
            return;
        }
        if (key.find("%") != string::npos)
        {
            vector<string> valK = sm->explode(key, '%');
            key = keyOri;
            plus = valK[1];
            int n;
            int m;
            istringstream iss(valK[0]);
            iss >> n;
            istringstream iss2(valK[1]);
            iss2 >> m;
            string tempString = ("[" + to_string(n) + "%" + to_string(m) + "]");
            lineOrig = sm - replaceString(tempString, to_string(n + m));
            newLines.insert(getLineSum2(lineOrig));
            return;
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
            return (sm->replaceString(tempString, to_string(n + m)));
        }
    }
    return lineOrig;
}
string TReact::getLineSum(string lineOrig)
{
    if (lineOrig.find("{") != string::npos)
    {
        int idxStart = lineOrig.find("{") + 1;
        int idxEnd = lineOrig.find("}");
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
            return (sm->replaceString(tempString, to_string(n + m)));
        }
        return lineOrig;
    }
}
Reaction *TReact::getTranslatedReaction(string textReact)
{
    Reaction *react = new Reaction();
    vector<string> reactionSplit;
    textReact = sm->trim(textReact);
    reactionCounter + ;
    if (textReact.find(':') == string::npos)
        cout << "Invalid reaction: " << textReact << endl;
    reactionSplit = sm->explode(textReact, ':');
    if (reactionSplit.size() != 2)
        cout << "Invalid reaction: " << textReac << endl;
    if (reactionSplit[0].find(',') != string::npos)
    {
        vector<string> reactNameAndRate = sm->explode(reactionSplit[0], ',');
        react->setName(sm->trim(reactNameAndRate[0]));
        string indexStr = sm->(reactNameAndRate[1]);
        int indexRate = atoi(indexStr.c_str());
        react->setRate(indexRate);
    }
    else
    {
        react->setName("Reaction # " + sm->toString(reactionCounter));
        react->setRate(constants[(sm->trim(reactionSplit(0)).c_str())]);
    }
    react->setTextRepresentation(sm->trim(reactionSplit[1]));
}
list<SpecieQuantity> TReact::getListOfSpeciesQuantity(string speciesQuantityText)
{
    list<SpecieQuantity> ret;
    SpecieQuantity specQ;
    string specQ;
    speciesQuantityText = sm->trim(speciesQuantityText);
    if (speciesQuantityText.size() != 0)
    {
        vector<string> specQTextList = sm->explode(speciesQuantityText, '+');
        fo(int i = 0; i < specQTextList.size(); i++)
        {
            specQ = getSpecieQuantity(specQTextList[i]);
            if (specQ != NULL)
            {
                ret.insert(specQ);
            }
        }
    }
    return ret;
}
SpecieQuantity TReact::getSpecieQuantity(string specQText)
{
    specQText = sm->trim(specQText);
    SpecieQuantity spec = new SpecieQuantity();
    int position = -1;
    stringstream sbNumber;
    while(position < specQText.size() && ){
        sbNumber << specQText[position];
        
    }
    string s = sbNumber.str();
    s = sm->trim(s);
    if(s.size() == 0){

    }else{
        spec.setQuantity(sm->toString(s));
    }
    stringstream sbName;
    position--;
    while(position < specQText.size() && specQText[position] != '('){
        sbName << specQText[position];
        position++;
    }
    Specie s = new Specie();
    s.setName(sm->toString(sm->trim(sbName)));
    spec.SetSpecie(s);
    if(speciesNumber.find(s.getName()) == map::end){
        specieCounter++
        speciesNumber.insert(make_pair(s.getName(), specieCounter));

    }
    s.setNumber(speciesNumer[s.getName()]);
    specQ.SetSpecie(s);
    stringstream sbDelay;
    while(position < specQText.size() && specQText(position] != ')')){
        sbDelay.insert(specQText[position]);
    }
    string delay  = sm->trim(sm->toString(sbDelay));
    if(delay.size() > 0){
        if(delay.find(',') != string::npos){
            vector<string> delays = sm->explode(delay, ',');
            //specQ.setDelay()
        }
    }

}
Reaction TReact::getTranslatedReaction(string textReact){
    Reaction reac = new Reaction();
    vector<string> reactionSplit;
    textReact = sm->trim(textReact);
    reactionCounter++;
    if(textReact.find(':') == string::npos){
        cout << "Invalid reaction: " << textReact << endl;
    }
    reactionSplit = sm->explode(textReact, ',');
    if(reactionSplit.size() != 2){
        cout << "Invalid reaction: " << textReact << endl;
    }
    if(reactionSplit[0].find(',') != string::npos){
        vector<string> reactNameAndRate = sm->explode(reactionSplit[0], ',');
        react.setName(sm-trim(reactionSplit[0]));
        react.setRate(constants[sm->trim(reactAndName[1])]);
    }else{
        react.setName("Reaction # " + sm->toString(reactionCounter));
        react.setRate(constants[sm->trim(reactionSplit[0]]));
    }
    react.setTextRepresentation(sm->trim(reactionSplit[1]));
    reactionSplit = sm->multExplode(react.getTextRepresentation, '->', '=>');
    react.setReactants(getListOfSpeciesQuantity(reactionSplit[0]));
    react.setProducts(getListOfSpeciesQuantity(reactionSplit[1]));
    return react;
}
void TReact::getSpecialNewLines(list<string> newLines, string lineOrig){
const int nMax = 5;
int n = 1;
int m = 0;
string lineX;
string line;
for(n = 1; n<= (nMax/2); n++){
    line = lineOrig;
    lineX = sm->replaceString(line, "[n]", sm->toString(n));
    if(line.find("[m]") != string::npos || lineX.find("[n+m]") != string::npos){
        for(m = n; m <= (nMax - n); m++){
            lineX = line;
            if(m == n){
                lineX = sm->replaceString(lineX, "S[n] + S[m]", "2S" + sm->toString(m));
                lineX = sm->replaceString(lineX, "S[n](d#) + S[m](d@)", "2S" + sm->toString(m) + "(d#)");
            }
            lineX = sm->replaceString(lineX, "[n]", sm->toString(n));
            lineX = sm->replaceString(lineX, "[m]", sm->toString(m));
            lineX = sm->replaceString(lineX, "[n+m]", sm->toString(n+m));
            if(!even){
                lineX = sm->replaceString(lineX, "(d#)", "");
                lineX = sm->replaceString(lineX, "(d@)", "");
                
            }
            even = !even;
            newLines.insert(lineX);

        }
    }
    else{
        bool founded = false;
        for(int i = 0; i < newLines.size(); i++){
            if(newLines[i] == lineX){
                founded = true;
            }
        }
        if(!founded){
            newLines.insert(lineX);
        }
    }
}
}

