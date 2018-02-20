#ifndef REACTFILE_H
#define REACTFILE_H

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "Reaction.h"
#include <fstream>

using namespace std;
namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}
class ReactFile
{
    public:
        ReactFile();
        void writeOutputFile(vector<Reaction*>& reactions, map<string, long int>& speciesNumber, map<string, long int>& speciesQuantity, string outputfile, vector<string>& modelrepresentation);
        virtual ~ReactFile();

    protected:

    private:


};

#endif // REACTFILE_H
