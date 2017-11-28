#include "Specie.h"

Specie::Specie(int maxSize){
    this->maxSize = maxSize;
}
Specie::~Specie(){
}
void Specie::insertSpecie(string id){
    if(species.size()<maxSize){
        species.push_back(id);
    }
}

string Specie::getIdByIndex(int index){
    if(index < species.size())
    return species[index]; //return the id
    else return "-1"; //invalid index
}
int Specie::getIndexById(string id){
    for(int i = 0; i<species.size(); i++){
        if(species[i] == id)
            return i; //return the index
    }
    return -1; //id not found
}

void Specie::printSpecies(){
    cout << "Printing species!" << endl;
    for(int i = 0; i<species.size(); i++)
    cout << "Specie[" << i << "]: " << species[i] << endl;
}