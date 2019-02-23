#ifndef DIRECTMETHOD_HPP
#define DIRECTMETHOD_HPP

#include <iostream>
#include "../include/SSA.hpp"

using namespace std;

class DirectMethod : public SSA
{
public:

    void perform(Model* model, double maximumTime, double initialTime, long int seed);
    virtual ~DirectMethod();

protected:
    double t;
    virtual void initialization(Model* model,  double maximumTime, double initialTime, long int seed); //read the model and initialization data structures
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
private:


};

#endif // DIRECTMETHOD_H
