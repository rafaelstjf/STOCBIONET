#include <iostream>
#include <string>
//#include "SSA.h"
#include "../include/DirectMethod.hpp"
#include "../include/FirstReactionMethod.hpp"
#include "../include/FirstReactionMethodDG.hpp"
#include "../include/NextReactionMethodSimplified.hpp"
#include "../include/NextReactionMethodClassic.hpp"


using namespace std;

int main(int argc, char *argv[])
{
    int op = 1;
    string filename;
    double simulTime = 0.0, beginTime = 0.0;
    SSA* simulation;
    if(argc == 5)
    {
        filename = argv[1];
        op = atoi(argv[2]);
        beginTime = atof(argv[3]);
        simulTime = atof(argv[4]);
    }
    else
    {
        cout <<"Insert the filename (with the extension):" << endl;
        cin >> filename;
        cout << "Insert the simulation time:" << endl;
        cin >> simulTime;
        cout << "Insert the initial time:" << endl;
        cin >> beginTime;
        cout << "Operations:\n 1 - Direct Method\n 2 - First Reaction Method\n 3 - First Reaction Method DG\n4 - Next Reaction Method Classic\n5 - First Reaction Method Simplified" << endl;
        cin >> op;
    }
    if(op==1)
        simulation = new DirectMethod();
    else if(op==2)
        simulation = new FirstReactionMethod();
    else if(op==3)
        simulation = new FirstReactionMethodDG();
    else if(op==4)
        simulation = new NextReactionMethodClassic();
    else if(op==5)
        simulation = new NextReactionMethodSimplified();
    else
    {
        cout << "Error. Invalid operation!" << endl;
        return -1;
    }
    simulation->perform(filename, simulTime, beginTime);
    delete simulation;
    return 0;
}
