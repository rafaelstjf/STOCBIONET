#include <iostream>
#include <string>
#include "DependencyGraph.hpp"
//#include "SSA.h"
#include "DirectMethod.hpp"
#include "FirstReactionMethod.hpp"
#include "FirstReactionMethodDG.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    int op = 1;
    string filename;
    double simulTime = 0.0;
    SSA* simulation;
    if(argc == 4)
    {
        filename = argv[1];
        op = atoi(argv[2]);
        simulTime = atof(argv[3]);
    }
    else
    {
        cout <<"Insert the filename (with the extension):" << endl;
        cin >> filename;
        cout << "Insert the simulation time:" << endl;
        cin >> simulTime;
        cout << "Operations:\n 1 - Direct Method\n 2 - First Reaction Method\n 3 - First Reaction Method DG" << endl;
        cin >> op;
    }
    if(op==1)
        simulation = new DirectMethod();
    else if(op==2)
        simulation = new FirstReactionMethod();
    else if(op==3)
        simulation = new FirstReactionMethodDG();
    else
    {
        cout << "Error. Invalid operation!" << endl;
        return -1;
    }
    simulation->perform(filename, simulTime);
    delete simulation;
    return 0;
}
