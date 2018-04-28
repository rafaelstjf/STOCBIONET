#ifndef FIRSTREACTIONMETHODDG_HPP
#define FIRSTREACTIONMETHODDG_HPP

#include <iostream>
#include "SSA.hpp"

using namespace std;

class FirstReactionMethodDG: public SSA
{
public:
    void perform(string filename, double simulTime);
    virtual ~FirstReactionMethodDG();

protected:

private:
    void initialization(string filename, double simulTime); //read the model and initialization data structures
    void calcPropensity(); //calculate the propensity function for all the reactions
    void printResult();
    void saveToFile();
    void calcPropOne(int index);
    double* t;
};

#endif // FIRSTREACTIONMETHODDG_H
