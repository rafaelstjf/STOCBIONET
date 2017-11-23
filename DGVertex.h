#ifndef DGVERTEX_H
#define DGVERTEX_H

#include <iostream>
#include <vector>
using namespace std;

class DGVertex
{
public:
    DGVertex(int id, int m);
    DGVertex();
    virtual ~DGVertex();
    void insertDependency(int val);
    void setDependencies();
    void setId(int id);
    void setN(int n);
    int* getDependencies();
    int* getSize();
    int* getId();
protected:

private:
    int m; //size of the dependencies vectory
    int n;//size of the list
    int id;//id of the vertex
    vector<int> dependencies;
};

#endif // DGVERTEX_H