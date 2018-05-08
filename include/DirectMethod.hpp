#ifndef DIRECTMETHOD_HPP
#define DIRECTMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"

using namespace std;

class DirectMethod : public SSA
{
public:

    void perform(string filename, double simulTime);
    virtual ~DirectMethod();

protected:
    double t;
    virtual void initialization(string filename,  double simultime); //read the model and initialization data structures
    virtual void calcPropensity(); //calculate the propensity function for all the reactions
    virtual void calcPropOne(int index);
    virtual void printResult();
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
private:


};

#endif // DIRECTMETHOD_H
