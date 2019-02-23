#include <iostream>
#include <string>
#include <cstdlib>
#include "../include/DirectMethod.hpp"
#include "../include/SortingDirectMethod.hpp"
#include "../include/FirstReactionMethod.hpp"
#include "../include/NextReactionMethod.hpp"
#include "../include/NextReactionMethodCompact.hpp"
#include "../include/SimplifiedNextReactionMethod.hpp"
#include "../include/RejectionMethod.hpp"
#include "../include/ModifiedNextReactionMethod.hpp"
#include "../include/Model.hpp"
#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#elif defined(_linux_)
#define PLATFORM_NAME "linux" // Linux
#endif

using namespace std;
void menu(Model *model, double &initialTime, double &maximumTime, long int &seed, string &op);
void chooseSimulation(string &op);
void clearScreen();
void postSimulation(SSA *simulation);
int main(int argc, char *argv[])
{
    char printOp;
    string filename;
    string op;
    double maximumTime = 0.0, initialTime = 0.0;
    SSA *simulation = nullptr;
    long int seed = -1;
    Model *model = new Model();

    if (argc == 5)
    {
        filename = argv[1];
        op = argv[2];
        initialTime = atof(argv[3]);
        maximumTime = atof(argv[4]);
        chooseSimulation(op);
        if (op == "DM")
            simulation = new DirectMethod();
        if (op == "SDM")
            simulation = new SortingDirectMethod();
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
        else if (op == "RM")
            simulation = new RejectionMethod();
        if (op == "error")
            return -1;
        else
        {
            cout << "Do you want to insert a custom seed? [y|n]" << endl;
            cin >> printOp;
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
        }
        model->loadModel(filename);
        if (!model->isModelLoaded())
            return -1;
        simulation->perform(model, maximumTime, initialTime, seed);
        postSimulation(simulation);
        delete simulation;
    }
    else
    {
        double repeat = true;
        while (repeat)
        {
            menu(model, initialTime, maximumTime, seed, op);
            if (op == "DM")
                simulation = new DirectMethod();
            if (op == "SDM")
                simulation = new SortingDirectMethod();
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
            else if (op == "RM")
                simulation = new RejectionMethod();
            simulation->perform(model, maximumTime, initialTime, seed);
            postSimulation(simulation);
            delete simulation;
            cout << "Do you want to perform another simulation? [y|n]" << endl;
            cin >> printOp;
            if (printOp != 'y' && printOp != 'Y')
                repeat = false;
            else
            {
                simulation = nullptr;
            }
        }
    }

    delete model;
    return 0;
}
void menu(Model *model, double &initialTime, double &maximumTime, long int &seed, string &op)
{
    string filename;
    char printOp;
    clearScreen();
    //prints the menu
    cout << "------------------------------------" << endl;
    cout << "---------------SSA------------------" << endl;
    cout << "------------------------------------" << endl;
    if (model->getFilename() == "")
    {
        //load a new model if there is any other loaded
        cout << "Insert the file path and name (with the extension):" << endl;
        while (!model->isModelLoaded())
        {
            cin >> filename;
            model->loadModel(filename);
        }
    }
    else
    {
        cout << "Current loaded model: " << model->getFilename() << endl;
        cout << "Do you want to load a new model? [y|n]" << endl;
        cin >> printOp;
        if (printOp == 'y' || printOp == 'Y')
        {
            delete model;
            model = new Model();
            cout << "Insert the file path and name (with the extension):" << endl;
            while (!model->isModelLoaded())
            {
                cin >> filename;
                model->loadModel(filename);
            }
        }
    }
    cout << "Insert the initial time:" << endl;
    cin >> initialTime;
    cout << "Insert the simulation time:" << endl;
    cin >> maximumTime;
    cout << "Methods:\nDM - Direct Method\nSDM - Sorting Direct Method\nFRM - First Reaction Method\nNRM - Next Reaction Method\nNRMC - Next Reaction Method Compact\nMNRM - Modified Next Reaction Method\nSNRM - Simplified Next Reaction Method\nRM - Rejection Method\n"
         << endl;
    cout << "Insert the Method:" << endl;
    double flag = true;
    while (flag)
    {
        cin >> op;
        chooseSimulation(op);
        if (op != "error")
            flag = false;
        else
        {
            cout << "Insert the Method again:" << endl;
        }
    }
    cout << "Do you want to insert a custom seed? [y|n]" << endl;
    cin >> printOp;
    if (printOp == 'y' || printOp == 'Y')
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
}
void chooseSimulation(string &op)
{
    if (op != "DM" && op != "SDM" && op != "FRM" && op != "NRM" && op != "NRMC" && op != "MNRM" && op != "SNRM" && op != "RM")
    {
        cout << "Error. Invalid operation!" << endl;
        op = "error";
    }
}
void postSimulation(SSA *simulation)
{
    char printOp;
    if (simulation->checkSucess())
    {
        cout << "Do you want to print the results? [y|n]" << endl;
        cin >> printOp;
        if (printOp == 'y' || printOp == 'Y')
            simulation->printResult();
        cout << "Do you want to save the results in a file? [y|n]" << endl;
        cin >> printOp;
        if (printOp == 'y' || printOp == 'Y')
            simulation->saveToFile();
    }
}
void clearScreen()
{
    //clear the screen
    if (PLATFORM_NAME == "windows")
        system("cls");
    if (PLATFORM_NAME == "linux")
        system("clear");
}