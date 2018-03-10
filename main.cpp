#include <iostream>
#include "DependencyGraph.h"
#include "SSA.h"
#include "DirectMethod.h"
using namespace std;

int main(int argc, char *argv[])
{
    Model* m = new Model();
    SSA* s = new DirectMethod();
    m->loadModel("entradaND.txt");
    DependencyGraph* dg = new DependencyGraph(m->getReacNumber(), m->getReactants(), m->getProducts(), m->getSpecNumber());
    dg->printGraph();
    return 0;
}
