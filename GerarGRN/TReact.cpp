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
        for(int j = 0; j< newLinesX.size(); j++){
            string y = sm-replaceChar(x, '{', ']');
            y = sm->replaceChar(y, '}', ']');
            getLines(newlines, y);

        }
        for(int j = 0; j< newLines.size(); j++){
            string line = newLines[j];
            if(sm->trim(line).size() >0){
                if(line.find('>') != string::npos){
                    react = getTranslatedReaction(line);
                    if(react != NULL){
                        ret.add(react);
                    }
                    modelRepresentation.add(sm->trim(line));
                }
                else
                {
                    con = sm->explode(line, '=');
                    if(con.size() != 2){
                        cout << "Invalid constant " << line << endl;
                    }
                    else if(constants.find(con[0]) != map::end){
                        cout << "Duplicate constant" << line << endl;
                    }else{
                        constants.insert(con[0], stoi(sm->replaceChar(con[1], '.', ',')));
                        modelRepresentation.add(sm->trim(line));
                    }
                }
            }
        }
    }
    speciesAndNumbers = speciesNumber;
    map<string, long int> speciesQuantity;
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
    textReact = sm->trim(textReact);
    reactionCounter+;
    if(textReact.find(':') == string::npos)
        cout << "Invalid reaction: " << textReact << endl;
    reactionSplit = sm->explode(textReact, ':');
    if(reactionSplit.size() != 2)
        cout << "Invalid reactio: " << textReac << endl;
    if(reactionSplit[0].find(',') != string::npos){
        vector<string> reactNameAndRate = sm->explode(reactionSplit[0], ',');
        react->setName(sm->trim(reactNameAndRate[0]));
        string indexStr = sm->(reactNameAndRate[1]);
        int indexRate = atoi(indexStr.c_str());
        react->setRate(indexRate);
    }
    else{
        react->setName("Reaction # " + sm->toString(reactionCounter));
        react->setRate(constants[(sm->trim(reactionSplit(0)).c_str())]);
    }
    react->setTextRepresentation(sm->trim(reactionSplit[1]));
    
}
list<SpecieQuantity> TReact::getListOfSpeciesQuantity(string speciesQuantityText){
    list<SpecieQuantity> ret;
    SpecieQuantity specQ;
    string specQ;
    speciesQuantityText = sm->trim(speciesQuantityText);
    if(speciesQuantityText.size()!=0){
        vector<string> specQTextList = sm->explode(speciesQuantityText, '+');
        fo(int i = 0; i< specQTextList.size(); i++){
            specQ = getSpecieQuantity(specQTextList[i]);
            if(specQ != NULL){
                ret.Add(specQ);
            }

        }
    }
    return ret;
}
SpecieQuantity TReact::getSpecieQuantity(string specQText){
    specQText = sm->trim(specQText);
    SpecieQuantity spec = new SpecieQuantity();
    int position = -1;
    
}