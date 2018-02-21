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
    stringstream line;
    fstream outf;
    string token;
    int specNumb;
    int reacNumb;
    vector<SpecieQuantity*> sQ;
    specNumb = speciesNumber.size();
    reacNumb = reactions.size();
    int reactants[reacNumb][specNumb];
    int products[reacNumb][specNumb];
    double delaysValues[reacNumb][specNumb];
    double delaysVariations[reacNumb][specNumb];
    i = 0;
    outf.open(outputfile, fstream::out);
    if(outf.is_open())
    {
        for(i = 0; i<reactions.size(); i++)
        {
            Reaction* r = reactions[i];
            sQ = r->getReactants();
            for(int l = 0; l < sQ.size(); l++)
            {
                reactants[i][sQ[l]->getSpecie()->getNumber()] = sQ[l]->getQuantity();
            }
            sQ = r->getProducts();
            for(int l = 0; l < sQ.size(); l++)
            {
                products[i][sQ[l]->getSpecie()->getNumber()] = sQ[l]->getQuantity();
                if(sQ[l]->getDelay()->getValue() > 0)
                    delaysValues[i][sQ[l]->getSpecie()->getNumber()] = sQ[l]->getDelay()->getValue();
                if(sQ[l]->getDelay()->getVariation() > 0)
                    delaysVariations[i][sQ[l]->getSpecie()->getNumber()] = sQ[l]->getDelay()->getVariation();
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
        while(it != speciesNumber.end())
        {
            line << token << it->first;
            token = ";";
            it++;
        }
        sw << line.str() << "\n";
        sw << "_end\n";
        sw << "#Species quantity.\n";
        sw << "_spec_qty:\n";
        sw << "_begin\n";
        line.clear();
        token = "";
        map<string, long int>::iterator itQ = speciesQuantity.begin();
        while(itQ != speciesQuantity.end())
        {
            line << token << patch::to_string(itQ->second);
            token = ";";
            itQ++;
        }
        sw << line.str() << "\n";
        sw << "_end\n";
        sw << "#Reagents. Lines = reactions. Columns = species\n";
        sw << "_reagents:\n";
        sw << "_begin\n";
        for(i = 0; i<reacNumb; i++)
        {
            token = "";
            line.clear();
            for(j = 0; j< specNumb; j++)
            {
                line << token << patch::to_string(reactants[i][j]) << "\n";
                token = ";";
            }
            sw << line.str() << "\n";
        }
        sw << "_end\n";
        sw << "#Products. Lines = reactions. Columns = species\n";
        sw << "_products:\n";
        sw << "_begin\n";
        for(i = 0; i<reacNumb; i++)
        {
            token = "";
            line.clear();
            for(j = 0; j< specNumb; j++)
            {
                line << token << patch::to_string(products[i][j]) << "\n";
                token = ";";
            }
            sw << line.str() << "\n";
        }
        sw << "_end\n";
        sw << "#Reaction constants for each reaction.\n";
        sw << "_rt_const:\n";
        sw << "_begin\n";
        token = "";
        line.clear();
        for(i = 0; i<reactions.size(); i++)
        {
            line << token + patch::to_string(reactions[i]->getRate());
            token = ";";
        }
        sw << line.str() << "\n";
        sw << "_end\n";

        sw << "#Delays for each product. Lines = reactions. Columns = species.\n";
        sw << "_p_delays:\n";
        sw << "_begin\n";
        for(i = 0; i < reacNumb; i++)
        {
            token = "";
            line.clear();
            for(j = 0; j< specNumb; j++)
            {
                line << token + patch::to_string(delaysValues[i][j]);
                token = ";";
            }
            sw << line.str() << "\n";
        }
        sw << "_end\n";
        sw << "#Delays variations for each product. Lines = reactions. Columns = species.\n";
        sw << "_p_delays:\n";
        sw << "_begin\n";
        for(i = 0; i < reacNumb; i++)
        {
            token = "";
            line.clear();
            for(j = 0; j< specNumb; j++)
            {
                line << token + patch::to_string(delaysVariations[i][j]);
                token = ";";
            }
            sw << line.str() << "\n";
        }
        sw << "_end\n";
        outf << sw.str();
        outf.close();
    }
    else
    {
        cout << "Impossible to save to file!" << endl;
    }


}
