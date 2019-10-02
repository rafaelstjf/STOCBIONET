#ifndef DGVERTEX_HPP
#define DGVERTEX_HPP

#include <iostream>
#include <vector>
using namespace std;

class DGVertex
{
public:
    DGVertex(int id, int n);
    DGVertex();
    virtual ~DGVertex();
    void insertDependency(int val);
    void setDependencies();
    void setId(int id);
    void setN(int n);
    int* getDependencies();
    int getSize();
    int getId();
protected:

private:
    int m; //size of the dependencies vector
    int n;//size of the list
    int id;//id of the vertex
    vector<int> dependencies;
};

#endif // DGVERTEX_H
