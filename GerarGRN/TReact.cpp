#include "TReact.h"

//patch necessary to use to_string function
namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}
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
vector<Reaction*> TReact::getReactions(string textToTranslate, map<string, long int>& speciesAndNumbers, map<string, long int>& speciesQuantity, vector<string>& modelRepresentation)
{
    //receives the raw text in textToTranslate string and saves it in the data structures
    Reaction* react;
    vector<Reaction*> ret;
    vector<string> newLinesX;
    vector<string> newLines;
    vector<string> con;
    //resets everything
    constants.clear();
    reactionCounter = 0;
    specieCounter = 0;
    even = false;

    //removes the newline (\n)
    textToTranslate = sm->replaceString(textToTranslate, "\r\n", "");
    textToTranslate = sm->replaceString(textToTranslate, "\n", "");

    //divides the text in to a vector separing by the ';'
    vector<string> lines = sm->explodeChar(textToTranslate, ';');
    for (int i = 0; i < lines.size(); i++)
    {
        string lineOrig = lines[i];
        newLines.clear();
        newLinesX.clear();
        getLines(newLinesX, lineOrig);
        for (int j = 0; j < newLinesX.size(); j++)
        {
            string x = newLinesX[j];
            x = sm ->replaceChar(x, '{', '[');
            x = sm->replaceChar(x, '}', ']');
            getLines(newLines, x);
        }
        for (int j = 0; j < newLines.size(); j++)
        {
            string line = newLines[j];
            line = sm->trim(line);
            if (line.size() > 0)
            {
                if (line.find('-') != string::npos) //contains reaction
                {
                    react = getTranslatedReaction(line);
                    if(react != NULL)
                    {
                        vector<SpecieQuantity*> spc = react->getReactants();
                        ret.push_back(react);
                    }

                    modelRepresentation.push_back(sm->trim(line));
                }
                else
                {
                    con = sm->explodeChar(line, '=');
                    if (con.size() != 2)
                    {
                        cout << "Invalid constant: " << line << endl;
                    }
                    else if (constants.find(con[0]) != constants.end())
                    {
                        cout << "Duplicate constant:" << con[0] << endl;
                    }
                    else
                    {
                        cout << con[0] << " " << con[1] << endl;
                        constants.insert(make_pair(con[0], atof(con[1].c_str())));
                        modelRepresentation.push_back(sm->trim(line));
                    }
                }
            }
        }
    }
    speciesAndNumbers = speciesNumber;
    speciesQuantity.clear();
    map<string, long int>::iterator it = speciesAndNumbers.begin();
    while (it != speciesAndNumbers.end())
    {
        //searches for the iterator's key
        if (constants.find(it->first) != constants.end())
        {
            long int temp = (long int) constants[it->first];
            speciesQuantity.insert(make_pair(it->first, temp));
        }
        else
        {

            speciesQuantity.insert(make_pair(it->first, 0));
        }
        it++;
    }
    cout << "Reactions sucessfuly imported" << endl;
    return ret;
}
void TReact::getLines(vector<string>& newLines, string lineOrig)
{
    size_t found;
    found = lineOrig.find("[...]");
    if (found != string::npos)
    {
        return; //string found
    }

    found = lineOrig.find("[");
    if (found != string::npos)
    {
        //string found
        int idxStart = lineOrig.find("[") + 1;
        int idxEnd = lineOrig.find("]");
        string key = lineOrig.substr(idxStart, idxEnd - idxStart);
        string keyOri = "";
        string plus = "";
        if (key.find("+") != string::npos)
        {
            vector<string> valK = sm->explodeChar(key, '+');
            keyOri = valK[0];
            key = keyOri;
            plus = valK[1];
            int n;
            //trying to parse
            istringstream iss(valK[0]);
            iss >> n;
            int m;
            istringstream iss2(valK[1]);
            iss2 >> m;
            string tempString = ("[" + patch::to_string(n) + "+" + patch::to_string(m) + "]");
            string nm = patch::to_string(n + m);
            lineOrig = sm->replaceString(lineOrig, tempString, nm);
            newLines.push_back(getLineSum2(lineOrig));
            return;
        }
        if (key.find("%") != string::npos)
        {
            vector<string> valK = sm->explodeChar(key, '%');
            keyOri = valK[0];
            key = keyOri;
            plus = valK[1];
            int n;
            int m;
            istringstream iss(valK[0]);
            iss >> n;
            istringstream iss2(valK[1]);
            iss2 >> m;
            string tempString = ("[" + patch::to_string(n) + "%" + patch::to_string(m) + "]");
            lineOrig = sm ->replaceString(lineOrig, tempString, patch::to_string((n/100)* m));
            newLines.push_back(getLineSum2(lineOrig));

            return;
        }
        int var_end;
        int var_start;
        if(keyOri.length() == 0)
        {
            string kp = key + "_start";
            var_start = constants.find(kp)->second;
            kp = key + "_end";
            var_end = constants.find(kp)->second;
        }
        else
        {
            string kp = keyOri + "_start";
            var_start = constants.find(kp)->second;
            kp = keyOri + "_end";
            var_end = constants.find(kp)->second;
        }
        string ori = lineOrig;
        //cout << "var_start: " << var_start << " var_end: " << var_end << endl;
        for(int i = var_start; i<=var_end; i++)
        {
            string temp = ('[' + key+ ']');
            ori = sm->replaceString(lineOrig, temp, patch::to_string(i));
            ori = sm->replaceString(ori, "[" + key + "+", "[" + patch::to_string(i) + "+");
            ori = sm->replaceString(ori, "+" + key + "]", "+" + patch::to_string(i) + "]");
            getLines(newLines, ori);
        }
    }
    else
    {
        string lineToSeek;
        lineToSeek = getLineSum(lineOrig);
        newLines.push_back(lineToSeek);
    }

}
string TReact::getLineSum2(string lineOrig)
{
    if (lineOrig.find("[") != string::npos)
    {
        int idxStart = lineOrig.find("[") + 1;
        int idxEnd = lineOrig.find("]");
        string key = lineOrig.substr(idxStart, idxEnd - idxStart);
        string keyOri = "";
        string plus = "";
        if (key.find("+") != string::npos)
        {
            vector<string> valK = sm->explodeChar(key, '+');
            keyOri = valK[0];
            key = keyOri;
            plus = valK[1];
            int n;
            istringstream iss(valK[0]);
            iss >> n;
            int m;
            istringstream iss2(valK[1]);
            iss2 >> m;
            string tempString = ("[" + patch::to_string(n) + "+" + patch::to_string(m) + "]");
            return (sm->replaceString(lineOrig, tempString, patch::to_string(n + m)));
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
            vector<string> valK = sm->explodeChar(key, '+');
            keyOri = valK[0];
            key = keyOri;
            plus = valK[1];
            int n;
            istringstream iss(valK[0]);
            iss >> n;
            int m;
            istringstream iss2(valK[1]);
            iss2 >> m;
            string tempString = ("{" + patch::to_string(n) + "+" + patch::to_string(m) + "}");

            return sm->replaceString(lineOrig, tempString, patch::to_string(n + m));
        }
    }
    return lineOrig;
}

vector<SpecieQuantity*> TReact::getListOfSpeciesQuantity(string speciesQuantityText)
{
    vector<SpecieQuantity*> ret;
    SpecieQuantity* specQ = new SpecieQuantity();
    speciesQuantityText = sm->trim(speciesQuantityText);
    if (speciesQuantityText.size() != 0)
    {
        vector<string> specQTextList = sm->explodeChar(speciesQuantityText, '+');
        for(int i = 0; i < specQTextList.size(); i++)
        {
            specQ = getSpecieQuantity(specQTextList[i]);
            ret.push_back(specQ);
        }
    }
    return ret;
}
SpecieQuantity* TReact::getSpecieQuantity(string specQText)
{
    specQText = sm->trim(specQText);
    SpecieQuantity* spec = new SpecieQuantity();
    int position = -1;
    stringstream sbNumber;
    while(position < specQText.size() && sm->isdigit(specQText[position]))
    {
        sbNumber << specQText[position];
        position++;
    }
    string s = sbNumber.str();
    s = sm->trim(s);
    if(s.size() == 0)
    {
        spec->setQuantity(1);
    }
    else
    {
        spec->setQuantity(atoi(patch::to_string(s).c_str()));
    }
    stringstream sbName;
    position--;
    while(position < specQText.size() && specQText[position] != '(')
    {
        sbName << specQText[position];
        position++;
    }
    Specie* sp = new Specie();
    sp->setName(patch::to_string(sm->trim(sbName.str())));
    spec->setSpecie(sp);
    if(speciesNumber.find(sp->getName()) == speciesNumber.end())
    {
        specieCounter++;
        speciesNumber.insert(make_pair(sp->getName(), specieCounter));

    }
    sp->setNumber(speciesNumber[sp->getName()]);
    spec->setSpecie(sp);
    Delay* specQDelay = new Delay();
    stringstream sbDelay;
    while(position < specQText.size() && specQText[position] != ')')
    {
        sbDelay << specQText[position];
        position++;
    }
    string delay  = sm->trim(patch::to_string(sbDelay));
    if(delay.size() > 0)
    {
        if(delay.find(',') != string::npos)
        {
            vector<string> delays = sm->explodeChar(delay, ',');
            specQDelay->setValue(constants[sm->trim(delays[0])]);
            specQDelay->setVariation(constants[sm->trim(delays[1])]);
        }
        else
        {
            specQDelay->setValue(constants[delay]);
        }
    }
    spec->setDelay(specQDelay);
    return spec;

}
Reaction* TReact::getTranslatedReaction(string textReact)
{
    Reaction* react = new Reaction();
    vector<string> reactionSplit;
    textReact = sm->trim(textReact);
    reactionCounter++;
    if(textReact.find(':') == string::npos)
    {
        cout << "Invalid reaction: " << textReact << endl;
        return NULL;
    }
    reactionSplit = sm->explodeChar(textReact, ':');
    if(reactionSplit.size() != 2)
    {
        cout << "Invalid reaction: " << textReact << endl;
        return NULL;
    }
    if(reactionSplit[0].find(',') != string::npos)
    {
        vector<string> reactNameAndRate = sm->explodeChar(reactionSplit[0], ',');
        react->setName(sm->trim(reactNameAndRate[0]));
        react->setRate(constants[sm->trim(reactNameAndRate[1])]);
    }
    else
    {
        react->setName("Reaction # " + patch::to_string(reactionCounter));
        react->setRate(constants[sm->trim(reactionSplit[0])]);
    }

    react->setTextRepresentation(sm->trim(reactionSplit[1]));
    reactionSplit = sm->explodeChar(react->getTextRepresentation(), '-');
    //reactants and products
    vector<SpecieQuantity*> r = getListOfSpeciesQuantity(reactionSplit[0]);
    vector<SpecieQuantity*> p = getListOfSpeciesQuantity(reactionSplit[1]);
    react->setReactants(r);
    react->setProducts(p);
    return react;
}
void TReact::getSpecialNewLines(vector<string>& newLines, string lineOrig)
{
    const int nMax = 5;
    int n = 1;
    int m = 0;
    string lineX;
    string line;
    for(n = 1; n<= (nMax/2); n++)
    {
        line = lineOrig;
        lineX = sm->replaceString(line, "[n]", patch::to_string(n));
        if(line.find("[m]") != string::npos || lineX.find("[n+m]") != string::npos)
        {
            for(m = n; m <= (nMax - n); m++)
            {
                lineX = line;
                if(m == n)
                {
                    lineX = sm->replaceString(lineX, "S[n] + S[m]", "2S" + patch::to_string(m));
                    lineX = sm->replaceString(lineX, "S[n](d#) + S[m](d@)", "2S" + patch::to_string(m) + "(d#)");
                }
                lineX = sm->replaceString(lineX, "[n]", patch::to_string(n));
                lineX = sm->replaceString(lineX, "[m]", patch::to_string(m));
                lineX = sm->replaceString(lineX, "[n+m]", patch::to_string(n+m));
                if(!even)
                {
                    lineX = sm->replaceString(lineX, "(d#)", "");
                    lineX = sm->replaceString(lineX, "(d@)", "");

                }
                even = !even;
                newLines.push_back(lineX);

            }
        }
        else
        {
            bool founded = false;
            for(int i = 0; i < newLines.size(); i++)
            {
                if(newLines[i] == lineX)
                {
                    founded = true;
                }
            }
            if(!founded)
            {
                newLines.push_back(lineX);
            }
        }
    }
}

