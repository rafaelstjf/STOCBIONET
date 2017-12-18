#ifndef SPECIE_H
#define SPECIE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Specie
{

  public:
    Specie(int maxSize);
    ~Specie();
    void insertSpecie(string id);
    int getIndexById(string id);
    string getIdByIndex(int index);
    void printSpecies();

  private:
    vector<string> species; //array of species' id
    int maxSize;            //size of the array of species
};
#endif