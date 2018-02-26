#include <iostream>
#include <string>
#include <map>
#include "TReact.h"
#include <sstream>
#include <fstream>
#include <map>
#include "Reaction.h"
#include "ReactFile.h"
#include "StringManager.h"
using namespace std;

int main()
{
    fstream inputfile;
    string filename;
    stringstream buffer;
    cout << "Type the name of the file:" << endl;
    cin >> filename;
    inputfile.open(filename, fstream::in);
    if(inputfile.is_open())
    {
        cout << "Reading the file..." << endl;
        buffer << inputfile.rdbuf();
        map<string, long int> speciesNumber;
        map<string, long int>speciesQuantity;
        vector<string> modelRepresentation;
        TReact* tr = new TReact();
        vector<Reaction*> reactions = tr->getReactions(buffer.str(), speciesNumber, speciesQuantity, modelRepresentation);
        ReactFile* wtf = new ReactFile();
        wtf->writeOutputFile(reactions, speciesNumber, speciesQuantity, "saida.txt", modelRepresentation);
        cout << "Size: " << reactions.size() << endl;
        delete wtf;
        delete tr;

    }
    else
    {
        cout << "file missing or incorrect!" << endl;
        exit(-1);
    }
}
