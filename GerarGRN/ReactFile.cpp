#include "ReactFile.h"

ReactFile::ReactFile()
{
    //ctor
}

ReactFile::~ReactFile()
{
    //dtor
}
void ReactFile::writeOutputFile(vector<Reaction*>& reactions, map<string, long int>& speciesNumber, map<string, long int>& speciesQuantity, string outputfile, vector<string>& modelrepresentation)
{
    int i;
    int j;
    string line;
    fstream outf;
    string token;
    int specNumb;
    int reacNumb;
    vector<SpecieQuantity*> sQ;
    vector<SpecieQuantity*> sQ2;
    specNumb = speciesNumber.size();
    reacNumb = reactions.size();
    int reactants[reacNumb][specNumb];
    int products[reacNumb][specNumb];
    double delaysValues[reacNumb][specNumb];
    double delaysVariations[reacNumb][specNumb];
    //cleaning the arrays
    for(i = 0; i < reacNumb; i++)
    {
        for(j = 0; j< specNumb; j++)
        {
            reactants[i][j] = 0.0;
            products[i][j] = 0.0;
            delaysValues[i][j] = 0.0;
            delaysVariations[i][j] = 0.0;
        }
    }

    i = 0;
    outf.open(outputfile, fstream::out); //openning the file
    if(outf.is_open())
    {
        for(i = 0; i<reactions.size(); i++)
        {
            Reaction* r = reactions[i];
            sQ = r->getReactants();
            for(j = 0; j < sQ.size(); j++)
            {
                reactants[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getQuantity();
            }
            sQ = r->getProducts();
            for(j = 0; j < sQ.size(); j++)
            {
                products[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getQuantity();
                if(sQ[j]->getDelay()->getValue() > 0.0)
                    delaysValues[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getDelay()->getValue();
                if(sQ[j]->getDelay()->getVariation() > 0.0)
                    delaysVariations[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getDelay()->getVariation();
            }
        }
        stringstream sw;
        sw << "#Modelo - begin\n";
        for(int k = 0; k<modelrepresentation.size(); k++)
        {
            sw << "#" << modelrepresentation[k] << ";\n";
        }
        sw << "#Modelo - end\n";
        sw << "#Reactions number.\n";
        sw << "_reac_num:" << patch::to_string(reacNumb) << "\n";
        sw << "#Species number.\n";
        sw << "_spec_num:" << patch::to_string(specNumb) << "\n";
        sw << "#Species names.\n";
        sw << "_spec_nam:\n";
        sw << "_begin\n";
        map<string, long int>::iterator it = speciesNumber.begin();
        token = "";
        line = "";
        while(it != speciesNumber.end())
        {
            line += (token + it->first);
            token = ";";
            it++;
        }
        sw << line << "\n";
        sw << "_end\n";
        sw << "#Species quantity.\n";
        sw << "_spec_qty:\n";
        sw << "_begin\n";
        line = "";
        token = "";
        map<string, long int>::iterator itQ = speciesQuantity.begin();
        while(itQ != speciesQuantity.end())
        {
            line +=(token + patch::to_string(itQ->second));
            token = ";";
            itQ++;
        }
        sw << line << "\n";
        sw << "_end\n";
        sw << "#Reagents. Lines = reactions. Columns = species\n";
        sw << "_reagents:\n";
        sw << "_begin\n";
        line = "";
        for(i = 0; i<reacNumb; i++)
        {
            token = "";
            line = "";
            for(j = 0; j< specNumb; j++)
            {
                line +=(token + patch::to_string(reactants[i][j]));
                token = ";";
            }
            sw << line << "\n";
        }
        sw << "_end\n";
        sw << "#Products. Lines = reactions. Columns = species\n";
        sw << "_products:\n";
        sw << "_begin\n";
        for(i = 0; i<reacNumb; i++)
        {
            token = "";
            line = "";
            for(j = 0; j< specNumb; j++)
            {
                line +=(token + patch::to_string(products[i][j]));
                token = ";";
            }
            sw << line << "\n";
        }
        sw << "_end\n";
        sw << "#Reaction constants for each reaction.\n";
        sw << "_rt_const:\n";
        sw << "_begin\n";
        token = "";
        line = "";
        for(i = 0; i<reactions.size(); i++)
        {
            line +=(token + patch::to_string(reactions[i]->getRate()));
            token = ";";
        }
        sw << line << "\n";
        sw << "_end\n";

        sw << "#Delays for each product. Lines = reactions. Columns = species.\n";
        sw << "_p_delays:\n";
        sw << "_begin\n";
        for(i = 0; i < reacNumb; i++)
        {
            token = "";
            line = "";
            for(j = 0; j< specNumb; j++)
            {
                line +=(token + patch::to_string(delaysValues[i][j]));
                token = ";";
            }
            sw << line << "\n";
        }
        sw << "_end\n";
        sw << "#Delays variations for each product. Lines = reactions. Columns = species.\n";
        sw << "_p_delays:\n";
        sw << "_begin\n";
        for(i = 0; i < reacNumb; i++)
        {
            token = "";
            line = "";
            for(j = 0; j< specNumb; j++)
            {
                line +=(token + patch::to_string(delaysVariations[i][j]));
                token = ";";
            }
            sw << line << "\n";
        }
        sw << "_end\n";
        cout << "--------------------------------------------------------" << endl;
        cout << "Output saved on " << outputfile << endl;
        cout << "Display output? type y for yes or n" << endl;
        char c;
        cin >> c;
        if(c == 'y' or c== 'Y')
            cout << sw.str() << endl;
        outf << sw.str();
        outf.close();
    }
    else
    {
        cout << "Impossible to save to file!" << endl;
    }


}
