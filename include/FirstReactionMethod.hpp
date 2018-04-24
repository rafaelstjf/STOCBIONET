#ifndef FIRSTREACTIONMETHOD_HPP
#define FIRSTREACTIONMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"

using namespace std;

class FirstReactionMethod: public SSA
{
public:
    void perform(string filename, double simulTime);
    virtual ~FirstReactionMethod();

protected:

private:
    void initialize(string filename, double simulTime); //read the model and initialize data structures
    void calcPropensity(); //calculate the propensity function for all the reactions
    void printResult();
    void saveToFile();
    void calcPropOne(int index);
    double* t;
};

#endif // FIRSTREACTIONMETHOD_H
