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
    for(i = 0; i < reacNumb; i++){
        for(j = 0; j< specNumb; j++){
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
<<<<<<< HEAD
            sQ = r->getProducts();
            for(j = 0; j < sQ.size(); j++)
            {
                products[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getQuantity();
                if(sQ[j]->getDelay()->getValue() > 0.0)
                    delaysValues[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getDelay()->getValue();
                if(sQ[j]->getDelay()->getVariation() > 0.0)
                    delaysVariations[i][sQ[j]->getSpecie()->getNumber()] = sQ[j]->getDelay()->getVariation();
=======
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
>>>>>>> origin/Without-SBML
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
<<<<<<< HEAD
            line +=(token + patch::to_string(itQ->second));
=======
            line += (token + patch::to_string(itQ->second));
>>>>>>> origin/Without-SBML
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
<<<<<<< HEAD
                line +=(token + patch::to_string(reactants[i][j]));
=======
                line += (token + patch::to_string(reactants[i][j]));
>>>>>>> origin/Without-SBML
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
<<<<<<< HEAD
                line +=(token + patch::to_string(products[i][j]));
                token = ";";
            }

=======
                line += (token + patch::to_string(products[i][j]));
                token = ";";
            }
>>>>>>> origin/Without-SBML
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
<<<<<<< HEAD
            line +=(token + patch::to_string(reactions[i]->getRate()));
=======
            line += (token + patch::to_string(reactions[i]->getRate()));
>>>>>>> origin/Without-SBML
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
<<<<<<< HEAD
                line +=(token + patch::to_string(delaysValues[i][j]));
                token = ";";
            }
=======
                cout << delaysValues[i][j] << " ";
                line += (token + patch::to_string(delaysValues[i][j]));
                token = ";";
            }
            cout << endl;
>>>>>>> origin/Without-SBML
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
<<<<<<< HEAD
                line +=(token + patch::to_string(delaysVariations[i][j]));
=======
                line += (token + patch::to_string(delaysVariations[i][j]));
>>>>>>> origin/Without-SBML
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
