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
            sQ2 = r->getProducts();
            for(int l = 0; l < sQ2.size(); l++)
            {
                products[i][sQ2[l]->getSpecie()->getNumber()] = sQ2[l]->getQuantity();
                if(sQ2[l]->getDelay()->getValue() > 0)
                    delaysValues[i][sQ2[l]->getSpecie()->getNumber()] = sQ2[l]->getDelay()->getValue();
                else
                    delaysValues[i][sQ2[l]]->getSpecie()->getNumber()] = 0;
                if(sQ2[l]->getDelay()->getVariation() > 0)
                    delaysVariations[i][sQ2[l]->getSpecie()->getNumber()] = sQ2[l]->getDelay()->getVariation();
                else
                    delaysVariations[i][sQ2[l]->getSpecie()->getNumber()] = 0;
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
            line += (token + patch::to_string(itQ->second));
            token = ";";
            itQ++;
        }
        sw << line << "\n";
        sw << "_end\n";
        sw << "#Reagents. Lines = reactions. Columns = species\n";
        sw << "_reagents:\n";
        sw << "_begin\n";
        for(i = 0; i<reacNumb; i++)
        {
            token = "";
            line = "";
            for(j = 0; j< specNumb; j++)
            {
                line += (token + patch::to_string(reactants[i][j]));
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
                line += (token + patch::to_string(products[i][j]));
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
            line += (token + patch::to_string(reactions[i]->getRate()));
            token = ";";
        }
        sw << line << "\n";
        sw << "_end\n";

        sw << "#Delays for each product. Lines = reactions. Columns = species.\n";
        sw << "_p_delays:\n";
        sw << "_begin\n";
        cout << "DELAY: " << endl;
        for(i = 0; i < reacNumb; i++)
        {
            token = "";
            line = "";
            for(j = 0; j< specNumb; j++)
            {
                cout << delaysValues[i][j] << " ";
                line += (token + patch::to_string(delaysValues[i][j]));
                token = ";";
            }
            cout << endl;
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
                line += (token + patch::to_string(delaysVariations[i][j]));
                token = ";";
            }
            sw << line << "\n";
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
