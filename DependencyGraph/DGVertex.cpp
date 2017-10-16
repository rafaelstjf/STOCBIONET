#include "DGVertex.h"

DGVertex::DGVertex()
{
    this->id = 0;
    this->m = 0;
    this->n = 0;
    dependencies.clear();

}
DGVertex::DGVertex(int id, int m)
{
    this->id = id;
    this->m = 0;
}

void DGVertex::insertDependency(int val) //insert a new dependency in the array's end
{
    bool duplicate = false;
    if(m<n && val<n)
    {
        for(int i = 0; i<m; i++)
        {
            if(dependencies[i]==val)
                duplicate = true;
        }
        if(!duplicate)
            dependencies.push_back(val);
        m++;
    }


}
int* DGVertex::getDependencies()//return the size of the array
{
    int* temp = new int[dependencies.size()];
    for(int i =0; i < dependencies.size(); i++)
        temp[i] = dependencies[i];
    return temp;
}
int* DGVertex::getSize()//return the dependencies' array
{

    return &m;
}
int* DGVertex::getId()
{
    return &id;
}
void DGVertex::setId(int id)
{
    this->id = id;
}
void DGVertex::setN(int n)
{
    this->n = n;
}
DGVertex::~DGVertex()
{
    dependencies.clear();
}
