#include "../include/DelayedDependencyGraph.hpp"
DelayedDependencyGraph::DelayedDependencyGraph()
{
    for (int i = 0; i < numSpecies; i++)
    {
        delete vertex[i];
    }
    delete[] vertex;
}
DelayedDependencyGraph::DelayedDependencyGraph(int **reactants, int **products, int numReactions, int numSpecies)
{
    createGraph(reactants, products, numReactions, numSpecies);
}
void DelayedDependencyGraph::createGraph(int **reactants, int **products, int numReactions, int numSpecies)
{
    this->numReactions = numReactions;
    this->numSpecies = numSpecies;
    //creates a array of DGVertex with the size of the number of species
    /*
        0->r0, r1,..., rm
        .
        .
        .
        numSpecies - 1 -> r0,r1,...rk
    */
    vertex = new DGVertex *[numSpecies];
    for (int i = 0; i < numSpecies; i++)
    {
        vertex[i] = new DGVertex();
        vertex[i]->setId(i);
        vertex[i]->setN(numReactions);
    }
    for (int i = 0; i < numSpecies; i++)
    {
        for (int j = 0; j < numReactions; j++)
        {
            if (reactants[i][j] != 0)
                insertDependency(i, j);
        }
    }
}
void DelayedDependencyGraph::insertDependency(int id, int val)
{

    if (id <= (numSpecies - 1) && (numSpecies - 1) >= 0)
        vertex[id]->insertDependency(val);
    else
        cout << "Invalid Id!" << endl;
}
int *DelayedDependencyGraph::getDependencies(int id)
{
    return vertex[id]->getDependencies();
}
int DelayedDependencyGraph::getDependenciesSize(int id)
{
    return vertex[id]->getSize();
}
void DelayedDependencyGraph::printGraph()
{
    int *dp;
    cout << "DELAYED DEPENDENCY GRAPH" << endl;
    for (int i = 0; i < numSpecies; i++)
    {
        cout << vertex[i]->getId() << " ->";
        dp = vertex[i]->getDependencies();
        for (int j = 0; j < vertex[i]->getSize(); j++)
            cout << " " << dp[j];
        cout << endl;
    }
}