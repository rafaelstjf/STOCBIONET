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
string getOutputFilename(string filename)
{
    string outputName = "";
    int fileFormat = 0;
    for(int i = 0; i < filename.size(); i++)
    {
        if(filename[i] != '.')
            outputName.append(1, filename[i]);
        else
        {
            fileFormat = i;
            break;
        }

    }
    outputName += "_output";
    if(fileFormat > 0)
    {
        for(int i = fileFormat; i < filename.size(); i++)
            outputName+= filename[i];
    }
    return outputName;
}
int main()
{
    fstream inputfile;
    string inFilename;
    stringstream buffer;
    cout << "Type the name of the file:" << endl;
    cin >> inFilename;
    inputfile.open(inFilename, fstream::in);
    if(inputfile.is_open())
    {
        cout << "Reading the file..." << endl;
        buffer << inputfile.rdbuf();
        map<string, long int> speciesNumber;
        map<string, long int>speciesQuantity;
        vector<string> modelRepresentation;
        TReact* tr = new TReact(true);
        vector<Reaction*> reactions = tr->getReactions(buffer.str(), speciesNumber, speciesQuantity, modelRepresentation);
        ReactFile* wtf = new ReactFile();
        string outFilename = getOutputFilename(inFilename);
        wtf->writeOutputFile(reactions, speciesNumber, speciesQuantity, outFilename, modelRepresentation);
        delete wtf;
        delete tr;

    }
    else
    {
        cout << "file missing or incorrect!" << endl;
        exit(-1);
    }
}
