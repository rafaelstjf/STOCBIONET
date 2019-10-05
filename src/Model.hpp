#ifndef MODEL_HPP
#define MODEL_HPP
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "model/TReact.hpp"
#include "model/Reaction.hpp"
#include "Dependency_Graph/DependencyGraph.hpp"
#include "Dependency_Graph/DelayedDependencyGraph.hpp"

using namespace std;

class Model
{
public:
    Model();
    ~Model();
    void loadModel(string filename);
    int **getReactants();
    int **getProducts();
    double *getReacRateArray();
    double **getDelaysValue();
    double **getDelaysVariation();
    DependencyGraph *getDGSelfEdge();
    //DependencyGraph *getDGNoSelfEdge();
    DelayedDependencyGraph *getDDG();
    int **getStoiMatrix();
    int *getInitialQuantity();
    int getSpecNumber();
    int getReacNumber();
    vector<string> getModelRepresentation();
    bool isModelLoaded();
    map<string, long int> getSpecNameNumber();
    string getFilename();
    void printModel();

private:
    int **reactants;          //reactants matrix
    int **products;           //products matrix
    double **delaysValue;     //delay value matrix
    double **delaysVariation; //delay variation matrix
    int specNumber;           //number of species in the model
    int reacNumber;           //number of reactions in the model
    string filename;
    double *reacRate; //array with the rate used in each reaction
    bool modelLoaded; //boolean to show if the model is loaded or not
    int **stoiMatrix;
    int *initialQuantity;                 //array with the species' initial quantities
    map<string, long int> specNameNumber; //associative container with the species' name and number
    vector<string> modelRepresentation;
    DependencyGraph *dgSelfEdges;
    DependencyGraph *dgNoSelfEdges;
    DelayedDependencyGraph *ddg;
    void buildStoichiometryMatrix();
    void buildDependencyGraphs();
    void clear();
};

#endif
