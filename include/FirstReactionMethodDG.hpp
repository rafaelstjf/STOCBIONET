#ifndef FIRSTREACTIONMETHODDG_HPP
#define FIRSTREACTIONMETHODDG_HPP

#include <iostream>
#include "FirstReactionMethod.hpp"

using namespace std;

class FirstReactionMethodDG : public FirstReactionMethod
{
  public:
    virtual void perform(string filename, double simulTime);
    virtual ~FirstReactionMethodDG();

  protected:
    virtual void initialization(string filename, double simulTime); //read the model and initialization data structures
    virtual void reacSelection();
    virtual void reacTimeGeneration();

  private:
};

#endif // FIRSTREACTIONMETHODDG_H
