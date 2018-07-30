#include <iostream>
#include <string>
#include "../include/DirectMethod.hpp"
#include "../include/FirstReactionMethod.hpp"
#include "../include/NextReactionMethod.hpp"
#include "../include/NextReactionMethodCompact.hpp"
#include "../include/SimplifiedNextReactionMethod.hpp"
#include "../include/ModifiedNextReactionMethod.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    char printOp;
    string filename;
    string op;
    double simulTime = 0.0, beginTime = 0.0;
    SSA *simulation;
    if (argc == 5)
    {
        filename = argv[1];
        op = argv[2];
        beginTime = atof(argv[3]);
        simulTime = atof(argv[4]);
    }
    else
    {
        cout << "Insert the filename (with the extension):" << endl;
        cin >> filename;
        cout << "Insert the simulation time:" << endl;
        cin >> simulTime;
        cout << "Insert the initial time:" << endl;
        cin >> beginTime;
        cout << "Operations:\nDM - Direct Method\nFRM - First Reaction Method\nNRM - Next Reaction Method\nNRMC - Next Reaction Method Compact\nMNRM - Modified Next Reaction Method\nSNRM - Simplified Next Reaction Method\n"
             << endl;
        cin >> op;
    }
    if (op == "DM")
        simulation = new DirectMethod();
    else if (op == "FRM")
        simulation = new FirstReactionMethod();
    else if (op == "NRM")
        simulation = new NextReactionMethod();
    else if (op == "NRMC")
        simulation = new NextReactionMethodCompact();
    else if (op == "MNRM")
        simulation = new ModifiedNextReactionMethod();
    else if (op == "SNRM")
        simulation = new SimplifiedNextReactionMethod();
    else
    {
        cout << "Error. Invalid operation!" << endl;
        return -1;
    }
    cout << "Do you want to insert a custom seed? [y|n]" << endl;
    cin >> printOp;
    long int seed = -1;
    if (printOp == 'y')
    {
        cout << "seed: ";
        string seedstr;
        cin >> seedstr;
        cout << endl;
        seed = atoi(seedstr.c_str());
        if (seed < 0)
        {
            cout << "Invalid seed! Performing the simulation using a random seed." << endl;
            seed = -1;
        }
    }
    simulation->perform(filename, simulTime, beginTime, seed);
    if (simulation->checkSucess())
    {
        cout << "Do you want to print the results? [y|n]" << endl;
        cin >> printOp;
        if (printOp == 'y')
            simulation->printResult();
        cout << "Do you want to save the results in a file? [y|n]" << endl;
        cin >> printOp;
        if (printOp == 'y')
            simulation->saveToFile();
    }
    delete simulation;
    return 0;
}
