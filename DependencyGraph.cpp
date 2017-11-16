#include "DependencyGraph.h"

DependencyGraph::DependencyGraph(int n, int** reactants, int** products, int numElements)
{

    int** affects;
    int* r;
    int* p;
    //graph struct
    this->n = n;
    this->numElements = numElements;
    vertex = new DGVertex*[n];
    for(int i = 0; i < n; i++)
    {
        vertex[i] = new DGVertex;
        vertex[i]->setId(i);
        vertex[i]->setN(n);
    }
//inserting dependencies

    affects = new int*[n];
    for(int i =0; i<n; i++)
    {
        r = extractElements(reactants, i);
        p = extractElements(products, i);
        affects[i] = unionSet(r, p);
    }

    for(int i =0; i<n; i++)
    {
        for(int j = 0; j< n; j++)
        {
            r = extractElements(reactants, j);
            int count = 0;
            int* inter = intersectionSet(affects[i],r);
            for(int k =0; k<numElements; k++)
            {
                if(inter[k]==1)
                    count++;
            }

            if(count>0)
                insertDependency(i, j);
        }
    }

}
void DependencyGraph::insertDependency(int id, int val)
{

    if(id<=(n-1) && (n-1)>=0)
        vertex[id]->insertDependency(val);
    else
        cout << "Invalid Id!" << endl;
}
int* DependencyGraph::getDependencies(int id)
{
    return vertex[id]->getDependencies();
}
int* DependencyGraph::getDependenciesSize(int id)
{
    return vertex[id]->getSize();
}
void DependencyGraph::printGraph()
{
    int* dp;
    cout <<"DEPENDENCY GRAPH " << endl;
    for(int i =0; i< n; i++)
    {
        cout << *vertex[i]->getId() << " ->";
        dp = vertex[i]->getDependencies();
        for(int k = 0; k < *vertex[i]->getSize(); k++)
            cout << " "  << dp[k];
        cout << endl;
    }
}
DependencyGraph::~DependencyGraph()
{
    for(int i = 0; i<n; i++)
    {
        DGVertex* v = vertex[i];
        delete v;
    }
    delete [] vertex;
}

int* DependencyGraph::unionSet(int* a, int* b)
//return a vector with the union of the arrays a and b
{
    int* un = new int[numElements];
    for(int i =0; i<numElements; i++)
    {
        if(b[i]!=a[i])
        {
            un[i] = 1;
        }
        else
            un[i] = 0;
    }
    return un;

}
int* DependencyGraph::extractElements(int** a, int c){
    //return an array with the elements of a determined reaction
    int* ar = new int[numElements];
    for(int i = 0;i<numElements; i++){
        ar[i] = a[i][c];
    }
    return ar;
}
int* DependencyGraph::intersectionSet(int* a, int* b)
//return a vector with the intersection of the arrays a and b
{
    int* in = new int[numElements];
    for(int i =0; i<numElements; i++)
    {
        if(b[i]==a[i])
        {
            in[i] = a[i];
        }
        else
            in[i] = 0;
    }
    return in;
}
