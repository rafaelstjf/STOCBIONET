#include "../include/DependencyGraph.hpp"

DependencyGraph::DependencyGraph(int numReactions, int **reactants, int **products, int numSpecies)
{
    int **affects; //set of substances that change quantity when the reaction i is executed
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
    //inserting dependencies
    affects = new int *[numReactions];
    for (int i = 0; i < numReactions; i++)
    {
        //affects = reactants U products
        affects[i] = unionSet(reactants[i], products[i]);
    }

    for (int i = 0; i < numReactions; i++)
    {
        for (int j = 0; j < numReactions; j++)
        {
            int count = 0;
            int *inter = intersectionSet(affects[i], reactants[j]);
            //if the intersection isn't an empty set so there is a dependency
            for (int k = 0; k < numSpecies; k++)
            {
                if (inter[k] >= 1)
                    count++;
            }

            if (count > 0)
                insertDependency(i, j);
            //j depends on i
        }
    }
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
int DependencyGraph::getDependenciesSize(int id)
{
    return vertex[id]->getSize();
}
void DependencyGraph::printGraph()
{
    int *dp;
    cout << "DEPENDENCY GRAPH " << endl;
    for (int i = 0; i < numReactions; i++)
    {
        cout << vertex[i]->getId() << " ->";
        dp = vertex[i]->getDependencies();
        for (int k = 0; k < vertex[i]->getSize(); k++)
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
        //lado direito para o esquerdo
        if (b[i] != a[i] && b[i] > a[i]) //a = 1
            un[i] = b[i] - a[i];
        else if(b[i] != a[i] && b[i] < a[i]) // a = 0
            un[i] = a[i] - b[i];
        else if(b[i] == a[i])
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
        if (b[i] == 0 && a[i] == 0)
            in[i] = 0;
        else if(b[i]!= 0 && a[i] != 0)
            in[i] = 1;
        else
            in[i] = 0;
    }
    return in;
}
DependencyGraph::~DependencyGraph(){
    for(int i = 0; i < numReactions; i++){
        delete vertex[i];
    }
    delete [] vertex;
}