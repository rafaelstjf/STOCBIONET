#include <iostream>
#include <string>
//#include "SSA.h"
#include "../include/DirectMethod.hpp"
#include "../include/FirstReactionMethod.hpp"
#include "../include/NextReactionMethodClassic.hpp"
#include "../include/NextReactionMethodCompact.hpp"


using namespace std;

int main(int argc, char *argv[])
{
    int op = 1;
    char printOp;
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
        cout << "Operations:\n 1 - Direct Method\n 2 - First Reaction Method\n 3 - Next Reaction Method Classic\n 4 - First Reaction Method Simplified" << endl;
        cin >> op;
    }
    if(op==1)
        simulation = new DirectMethod();
    else if(op==2)
        simulation = new FirstReactionMethod();
    else if(op==3)
        simulation = new NextReactionMethodClassic();
    else if(op==4)
        simulation = new NextReactionMethodCompact();
    else
    {
        cout << "Error. Invalid operation!" << endl;
        return -1;
    }
    simulation->perform(filename, simulTime, beginTime);
    cout << "Do you want to print the results? (y-yes or n-no)" << endl;
    cin >> printOp;
    if(printOp == 'y')
        simulation->printResult();

    delete simulation;
    return 0;
}
