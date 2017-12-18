#include "DependencyGraph.h"

DependencyGraph::DependencyGraph(int numReactions, double **reactants, double **products, int numElements)
{
    int **react;
    int **prod;
    int **affects;
    int *r;
    int *p;
    //graph struct
    this->numReactions = numReactions;
    this->numElements = numElements;
    vertex = new DGVertex *[numReactions];
    for (int i = 0; i < numReactions; i++)
    {
        vertex[i] = new DGVertex;
        vertex[i]->setId(i);
        vertex[i]->setN(numReactions);
    }
    //creating 2 matrix with 0-1 elements
    react = new int *[numElements];
    prod = new int *[numElements];
    for (int i = 0; i < numElements; i++)
    {
        react[i] = new int[numReactions];
        prod[i] = new int[numReactions];
    }
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numReactions; j++)
        {
            if (reactants[i][j] != 0.0)
                react[i][j] = 1;
            else
                react[i][j] = 0;

            if (products[i][j] != 0.0)
                prod[i][j] = 1;
            else
                prod[i][j] = 0
        }
    }
    //inserting dependencies

    affects = new int *[numReactions];
    for (int i = 0; i < numReactions; i++)
    {
        r = extractElements(reac, i);
        p = extractElements(prod, i);
        affects[i] = unionSet(r, p);
    }

    for (int i = 0; i < numReactions; i++)
    {
        for (int j = 0; j < numReactions; j++)
        {
            r = extractElements(reactants, j);
            int count = 0;
            int *inter = intersectionSet(affects[i], r);
            for (int k = 0; k < numElements; k++)
            {
                if (inter[k] == 1)
                    count++;
            }

            if (count > 0)
                insertDependency(i, j);
        }
    }
    delete react;
    delete prod;
}
void DependencyGraph::insertDependency(int id, int val)
{

    if (id <= (numReactions - 1) && (numReactions - 1) >= 0)
        vertex[id]->insertDependency(val);
    else
        cout << "Invalid Id!" << endl;
}
int *DependencyGraph::getDependencies(int id)
{
    return vertex[id]->getDependencies();
}
int *DependencyGraph::getDependenciesSize(int id)
{
    return vertex[id]->getSize();
}
void DependencyGraph::printGraph()
{
    int *dp;
    cout << "DEPENDENCY GRAPH " << endl;
    for (int i = 0; i < numReactions; i++)
    {
        cout << *vertex[i]->getId() << " ->";
        dp = vertex[i]->getDependencies();
        for (int k = 0; k < *vertex[i]->getSize(); k++)
            cout << " " << dp[k];
        cout << endl;
    }
}
DependencyGraph::~DependencyGraph()
{
    for (int i = 0; i < numReactions; i++)
    {
        DGVertex *v = vertex[i];
        delete v;
    }
    delete[] vertex;
}

int *DependencyGraph::unionSet(int *a, int *b)
//return a vector with the union of the arrays a and b
{
    int *un = new int[numElements];
    for (int i = 0; i < numElements; i++)
    {
        if (b[i] != a[i])
        {
            un[i] = 1;
        }
        else
            un[i] = 0;
    }
    return un;
}
int *DependencyGraph::extractElements(int **a, int c)
{
    //return an array with the elements of a determined reaction
    int *ar = new int[numElements];
    for (int i = 0; i < numElements; i++)
    {
        ar[i] = a[i][c];
    }
    return ar;
}
int *DependencyGraph::intersectionSet(int *a, int *b)
//return a vector with the intersection of the arrays a and b
{
    int *in = new int[numElements];
    for (int i = 0; i < numElements; i++)
    {
        if (b[i] == a[i])
        {
            in[i] = a[i];
        }
        else
            in[i] = 0;
    }
    return in;
}