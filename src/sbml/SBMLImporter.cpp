#include "SBMLImporter.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

#ifdef STOCBIONET_HAVE_LIBSBML
#include <sbml/SBMLTypes.h>
#endif

using namespace std;

namespace
{
string lowerCopy(string value)
{
    transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return (char)tolower(c); });
    return value;
}

string sanitizeId(const string &id)
{
    string out;
    for (char c : id)
    {
        if (isalnum((unsigned char)c) || c == '_')
            out += c;
        else
            out += '_';
    }
    return out.empty() ? "unnamed" : out;
}

#ifdef STOCBIONET_HAVE_LIBSBML
double parameterValue(const libsbml::Model *model, const libsbml::KineticLaw *law, const string &name, bool &found)
{
    found = false;
    if (law != nullptr)
    {
        const libsbml::Parameter *local = law->getParameter(name);
        if (local != nullptr && local->isSetValue())
        {
            found = true;
            return local->getValue();
        }
    }
    const libsbml::Parameter *global = model->getParameter(name);
    if (global != nullptr && global->isSetValue())
    {
        found = true;
        return global->getValue();
    }
    return 0.0;
}

double numericKineticLaw(const libsbml::Model *model, const libsbml::KineticLaw *law, bool &ok)
{
    ok = false;
    if (law == nullptr || law->getMath() == nullptr)
        return 0.0;

    const libsbml::ASTNode *math = law->getMath();
    if (math->isNumber())
    {
        ok = true;
        return math->getReal();
    }
    if (math->isName())
    {
        bool found = false;
        double value = parameterValue(model, law, math->getName(), found);
        ok = found;
        return value;
    }
    return 0.0;
}

string speciesTerm(const libsbml::SpeciesReference *ref, double delay, double variation, const string &delayName, const string &variationName)
{
    stringstream term;
    double stoich = ref->isSetStoichiometry() ? ref->getStoichiometry() : 1.0;
    if (stoich != 1.0)
        term << (long int)stoich;
    term << sanitizeId(ref->getSpecies());
    if (delay > 0.0 || variation > 0.0)
    {
        term << "(" << delayName;
        if (variation > 0.0)
            term << "," << variationName;
        term << ")";
    }
    return term.str();
}
#endif
}

bool SBMLImporter::canLoad(const string &filename)
{
    string name = lowerCopy(filename);
    return (name.size() >= 4 && name.substr(name.size() - 4) == ".xml") || (name.size() >= 5 && name.substr(name.size() - 5) == ".sbml");
}

bool SBMLImporter::load(const string &filename, string &translatedModel, string &errorMessage)
{
#ifndef STOCBIONET_HAVE_LIBSBML
    (void)filename;
    translatedModel.clear();
    errorMessage = "libSBML is not available in this build.";
    return false;
#else
    libsbml::SBMLDocument *document = libsbml::readSBMLFromFile(filename.c_str());
    if (document == nullptr)
    {
        errorMessage = "Unable to read SBML document.";
        return false;
    }
    if (document->getNumErrors() > 0)
    {
        stringstream ss;
        ss << "SBML validation reported " << document->getNumErrors() << " issue(s).";
        errorMessage = ss.str();
    }
    const libsbml::Model *model = document->getModel();
    if (model == nullptr)
    {
        delete document;
        errorMessage = "SBML document does not contain a model.";
        return false;
    }

    stringstream out;
    for (unsigned int i = 0; i < model->getNumParameters(); ++i)
    {
        const libsbml::Parameter *parameter = model->getParameter(i);
        if (parameter->isSetValue())
            out << sanitizeId(parameter->getId()) << "=" << parameter->getValue() << ";\n";
    }
    for (unsigned int i = 0; i < model->getNumSpecies(); ++i)
    {
        const libsbml::Species *species = model->getSpecies(i);
        double amount = 0.0;
        if (species->isSetInitialAmount())
            amount = species->getInitialAmount();
        else if (species->isSetInitialConcentration())
            amount = species->getInitialConcentration();
        out << sanitizeId(species->getId()) << "=" << amount << ";\n";
    }

    for (unsigned int i = 0; i < model->getNumReactions(); ++i)
    {
        const libsbml::Reaction *reaction = model->getReaction(i);
        const libsbml::KineticLaw *law = reaction->getKineticLaw();
        bool rateOk = false;
        double rate = numericKineticLaw(model, law, rateOk);
        if (!rateOk)
        {
            delete document;
            errorMessage = "Reaction '" + reaction->getId() + "' has a kineticLaw that is not a numeric constant or single parameter.";
            return false;
        }

        bool foundDelay = false, foundVariation = false;
        double delay = parameterValue(model, law, "delay", foundDelay);
        double variation = parameterValue(model, law, "delay_variation", foundVariation);
        string reactionId = sanitizeId(reaction->getId());
        string delayName = "__delay_" + reactionId;
        string variationName = "__delay_variation_" + reactionId;
        out << "__rate_" << reactionId << "=" << rate << ";\n";
        if (foundDelay)
            out << delayName << "=" << delay << ";\n";
        if (foundVariation)
            out << variationName << "=" << variation << ";\n";

        out << reactionId << ",__rate_" << reactionId << ":";
        for (unsigned int j = 0; j < reaction->getNumReactants(); ++j)
        {
            if (j > 0)
                out << " + ";
            out << speciesTerm(reaction->getReactant(j), 0.0, 0.0, delayName, variationName);
        }
        out << " -> ";
        for (unsigned int j = 0; j < reaction->getNumProducts(); ++j)
        {
            if (j > 0)
                out << " + ";
            out << speciesTerm(reaction->getProduct(j), foundDelay ? delay : 0.0, foundVariation ? variation : 0.0, delayName, variationName);
        }
        out << ";\n";
    }

    translatedModel = out.str();
    delete document;
    return true;
#endif
}
