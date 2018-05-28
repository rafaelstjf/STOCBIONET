#include "../include/DependencyGraphNRM.hpp"

DependencyGraphNRM::DependencyGraphNRM(int numReactions, int **reactants, int **products, int numSpecies)
{
        createGraph(numReactions,reactants,products,numSpecies);
}
void DependencyGraphNRM::createGraph(int numReactions, int **reactants, int **products, int numSpecies)
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
            {
                if (i != j) //doesn't insert the self dependency
                    insertDependency(i, j);
            }
            //j depends on i
        }
    }
}
