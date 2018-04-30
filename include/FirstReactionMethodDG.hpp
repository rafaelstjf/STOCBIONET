#ifndef FIRSTREACTIONMETHODDG_HPP
#define FIRSTREACTIONMETHODDG_HPP

#include <iostream>
#include "FirstReactionMethod.hpp"

using namespace std;

class FirstReactionMethodDG : public FirstReactionMethod
{
  public:
    void perform(string filename, double simulTime);
    virtual ~FirstReactionMethodDG();

  protected:
    void initialization(string filename, double simulTime); //read the model and initialization data structures
    void saveToFile();
    void reacSelection();

  private:
};

#endif // FIRSTREACTIONMETHODDG_H
