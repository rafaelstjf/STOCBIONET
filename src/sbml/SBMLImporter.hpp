#ifndef SBMLIMPORTER_HPP
#define SBMLIMPORTER_HPP

#include <map>
#include <string>
#include <vector>

class SBMLImporter
{
public:
    static bool canLoad(const std::string &filename);
    static bool load(const std::string &filename,
                     std::string &translatedModel,
                     std::string &errorMessage);
};

#endif
