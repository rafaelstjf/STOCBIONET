#ifndef DIRECTMETHOD_HPP
#define DIRECTMETHOD_HPP

#include <iostream>
#include "SSA.hpp"

using namespace std;

class DirectMethod : public SSA
{
public:

    void perform(string filename, double simulTime);
    virtual ~DirectMethod();

private:
    void initialize(string filename,  double simultime); //read the model and initialize data structures
    void calcPropensity(); //calculate the propensity function for all the reactions
    void calcPropOne(int index);
    void printResult();
    void saveToFile();


};

#endif // DIRECTMETHOD_H
