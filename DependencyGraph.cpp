#include "DependencyGraph.h"

DependencyGraph::DependencyGraph(int numReactions, int **reactants, int **products, int numSpecies)
{
    int **affects; //set of substances that change quantity when the reaction i is executed
    int **react;
    int **prod;
    //graph struct
    this->numReactions = numReactions;
    this->numSpecies = numSpecies;
    vertex = new DGVertex *[numReactions];
    for (int i = 0; i < numReactions; i++)
    {
        vertex[i] = new DGVertex;
        vertex[i]->setId(i);
        vertex[i]->setN(numReactions);
    }
    //creating 2 matrix with 0-1 elements
    react = new int *[numReactions];
    prod = new int *[numReactions];
    for (int i = 0; i < numReactions; i++)
    {
        react[i] = new int[numSpecies];
        prod[i] = new int[numSpecies];
    }
    for (int i = 0; i < numReactions; i++)
    {
        for (int j = 0; j < numSpecies; j++)
        {
            if (reactants[i][j] != 0)
                react[i][j] = 1;
            else
                react[i][j] = 0;

            if (products[i][j] != 0)
                prod[i][j] = 1;
            else
                prod[i][j] = 0;
        }
    }
    //inserting dependencies
    affects = new int *[numReactions];
    for (int i = 0; i < numReactions; i++)
    {
        //affects = reactants U products
        affects[i] = unionSet(react[i], products[i]);
    }

    for (int i = 0; i < numReactions; i++)
    {
        for (int j = 0; j < numReactions; j++)
        {
            int count = 0;
            int *inter = intersectionSet(affects[i], react[j]);
            //if the intersection isn't an empty set so there is a dependency
            for (int k = 0; k < numSpecies; k++)
            {
                if (inter[k] == 1)
                    count++;
            }

            if (count > 0)
                insertDependency(i, j);
                //j depends on i
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
    int *un = new int[numSpecies];
    for (int i = 0; i < numSpecies; i++)
    {
        if (b[i] == 0 && b[i]!= a[i]) //a = 1
            un[i] = 1;
        else if(b[i] != 0 && b[i]!= a[i]) // a = 0
            un[i] = 1;
        else if(b[i] == 1 && a[i] == 1)
            un[i] = 0;
        else
            un[i] = 0;
    }
    return un;
}
int *DependencyGraph::intersectionSet(int *a, int *b)
//return a vector with the intersection of the arrays a and b
{
    int *in = new int[numSpecies];
    for (int i = 0; i < numSpecies; i++)
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
