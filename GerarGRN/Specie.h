#ifndef SPECIE_H
#define SPECIE_H

#include <iostream>
#include <string>

class Specie
{
  private:
    string name;
    long int number;

  public:
    Specie();
    ~Specie();
    void setName(string name);
    void setNumber(long int number);
    string getName();
    long int getNumber();
};
#endif