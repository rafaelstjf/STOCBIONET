#include "../include/DependencyGraph.hpp"
DependencyGraph::DependencyGraph()
{
}
DependencyGraph::DependencyGraph(double selfEdges, Model *model)
{
    createGraph(selfEdges, model);
}
void DependencyGraph::createGraph(double selfEdges, Model *model)
{

    int **affects; //set of substances that change quantity when the reaction i is executed
    //graph struct
    this->selfEdges = selfEdges;
    numReactions = model->getReacNumber();
    numSpecies = model->getSpecNumber();
    vertex = new DGVertex *[numReactions];
    for (int i = 0; i < numReactions; i++)
    {
        vertex[i] = new DGVertex();
        vertex[i]->setId(i);
        vertex[i]->setN(numReactions);
    }
    //inserting dependencies
    affects = new int *[numReactions];
    for (int i = 0; i < numReactions; i++)
    {
        //affects = reactants U products
        affects[i] = unionSet(model->getReactants(), model->getProducts(), model->getDelaysValue(), i);
    }

    for (int i = 0; i < numReactions; i++)
    {
        for (int j = 0; j < numReactions; j++)
        {
            int count = 0;
            int *inter = intersectionSet(affects[i], model->getReactants(), j);
            //if the intersection isn't an empty set so there is a dependency
            for (int k = 0; k < numSpecies; k++)
            {
                if (inter[k] >= 1)
                    count++;
            }
            delete[] inter;
            if (selfEdges == true)
            {
                if (count > 0 || i == j)
                { //i==j always insert a self-edge
                    insertDependency(i, j);
                }
            }
            else
            {
                if (count > 0)
                {
                    if (i != j) //doesn't insert the self dependency
                        insertDependency(i, j);
                }
            }

            //j depends on i
        }
    }
    for (int i = 0; i < numReactions; i++)
    {
        delete[] affects[i];
    }
    delete[] affects;
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
int *DependencyGraph::unionSet(int **reactants, int **products, double **delay, int reacIndex)
//return reactants vector with the union of the arrays reactants and products
{
    int *un = new int[numSpecies];
    for (int i = 0; i < numSpecies; i++)
    {
        //lado direito para o esquerdo
        if (delay[i][reacIndex] > 0.0)
            un[i] = reactants[i][reacIndex];
        else if (products[i][reacIndex] != reactants[i][reacIndex] && products[i][reacIndex] > reactants[i][reacIndex]) //reactants = 1
            un[i] = products[i][reacIndex] - reactants[i][reacIndex];
        else if (products[i][reacIndex] != reactants[i][reacIndex] && products[i][reacIndex] < reactants[i][reacIndex]) // reactants = 0
            un[i] = reactants[i][reacIndex] - products[i][reacIndex];
        else if (products[i][reacIndex] == reactants[i][reacIndex])
            un[i] = 0;
    }
    return un;
}
int *DependencyGraph::intersectionSet(int *affects, int **reactants, int reacIndex)
//return affects vector with the intersection of the arrays affects and reactants
{
    int *in = new int[numSpecies];
    for (int i = 0; i < numSpecies; i++)
    {
        if (reactants[i][reacIndex] == 0 && affects[i] == 0)
            in[i] = 0;
        else if (reactants[i][reacIndex] != 0 && affects[i] != 0)
            in[i] = 1;
        else
            in[i] = 0;
    }
    return in;
}
DependencyGraph::~DependencyGraph()
{
    for (int i = 0; i < numReactions; i++)
    {
        delete vertex[i];
    }
    delete[] vertex;
}
