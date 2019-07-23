#include <iostream>
#include <fstream>
#include <string>
#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#include <windows.h>
#elif defined(__linux__)
#define PLATFORM_NAME "linux" // Linux
#include <unistd.h>
#else
#define PLATFORM_NAME "unknown"
#endif
#include "DirectMethod.hpp"
#include "SortingDirectMethod.hpp"
#include "OptimizedDirectMethod.hpp"
#include "FirstReactionMethod.hpp"
#include "NextReactionMethod.hpp"
#include "NextReactionMethodCompact.hpp"
#include "SimplifiedNextReactionMethod.hpp"
#include "RejectionMethod.hpp"
#include "ModifiedNextReactionMethod.hpp"
#include "Model.hpp"

using namespace std;

//declaration
SSA *allocateSimulation(string &op);
void postSimulation(SSA *simulation);
void runBatchSimulation(Model *model, SSA *simulation, double &initialTime, double &maximumTime, string &op, long int &seed, int &numSimulations);
void menu(Model *model, double &initialTime, double &maximumTime, long int &seed, string &op);
void clearScreen();
void sleepFor(int sleepMs);

int main(int argc, char *argv[])
{
    char printOp;
    string filename, op;
    double maximumTime = 0.0, initialTime = 0.0;
    SSA *simulation = nullptr;
    long int seed = -1;
    Model *model = new Model();
    int numSimulations = 0;
    //set variables
    if (argc >= 5)
    {
        filename = argv[1];
        op = argv[2];
        initialTime = atof(argv[3]);
        maximumTime = atof(argv[4]);
        model->loadModel(filename);
        if (!model->isModelLoaded())
            return -2;
        if (argc == 6)
        {
            //run the batch simulation
            numSimulations = atoi(argv[5]);
            runBatchSimulation(model, simulation, initialTime, maximumTime, op, seed, numSimulations);
        }
        else
        {
            //run single simulation
            simulation = allocateSimulation(op);
            if (simulation != nullptr)
            {
                simulation->perform(model, maximumTime, initialTime, seed);
                postSimulation(simulation);
            }
            else
            {
                delete model;
                delete simulation;
                return -1;
            }
        }
    }
    else
    {
        //run interative simulation
        bool repeat = true;
        while (repeat)
        {
            menu(model, initialTime, maximumTime, seed, op);
            cout << "Do you want to perform a batch simulation? [y|n]" << endl;
            cin >> printOp;
            if (printOp == 'y')
            {
                repeat = false;
                cout << "Insert the number of simulations:" << endl;
                cin >> numSimulations;
                runBatchSimulation(model, simulation, initialTime, maximumTime, op, seed, numSimulations);
            }
            else
            {
                simulation = allocateSimulation(op);
                simulation->perform(model, maximumTime, initialTime, seed);
                postSimulation(simulation);
                clearScreen();
                cout << "Do you want to perform another simulation? [y|n]" << endl;
                cin >> printOp;
                if (printOp != 'y' && printOp != 'Y')
                    repeat = false;
                else
                {
                    delete simulation;
                }
            }
        }
    }
    delete model;
    delete simulation;
    return 0;
}
//definition
SSA *allocateSimulation(string &op)
{
    SSA *simulation = nullptr;
    if (op == "DM")
        simulation = new DirectMethod();
    else if (op == "SDM")
        simulation = new SortingDirectMethod();
    else if (op == "ODM")
        simulation = new OptimizedDirectMethod();
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
    return simulation;
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
void runBatchSimulation(Model *model, SSA *simulation, double &initialTime, double &maximumTime, string &op, long int &seed, int &numSimulations)
{
    vector<double> reacExe;
    vector<double> reacPerSec;
    vector<unsigned long int> seedArray;
    double sumReacExe = 0;
    double sumReacPerSec = 0;
    int curSimulation = 0;
    char saveOp1 = 'n', saveOp2 = 'n';
    cout << "Do you want to save the simulation's log and the details in a file? [y|n]" << endl;
    cin >> saveOp1;
    if (saveOp1 != 'y')
    {
        cout << "Do you want to save only the simulation's details in a file? [y|n]" << endl;
        cin >> saveOp2;
    }
    while (curSimulation < numSimulations)
    {
        curSimulation++;
        simulation = allocateSimulation(op);
        if (simulation == nullptr)
        {
            cout << "Error during batch simulation!" << endl;
            break;
        }
        else
        {
            simulation->perform(model, maximumTime, initialTime, seed);
            if (saveOp1 == 'y')
            {
                simulation->saveToFile();
                sleepFor(1000);
            }
            else if (saveOp2 == 'y')
            {
                simulation->saveDetailsToFile();
                sleepFor(1000);
            }
            seedArray.push_back(simulation->getSeed());
            reacPerSec.push_back(simulation->getReacPerSecond());
            reacExe.push_back(simulation->getNumberReacExecuted());
            delete simulation;
        }
    }
    fstream bashOutput;
    bashOutput.open("bashOutput.csv", fstream::out | fstream::trunc);
    bashOutput << "Number of executed reactions; Number of reactions per second; Seeds used " << endl;
    for (int i = 0; i < numSimulations; i++)
    {
        bashOutput << reacExe[i] << "; " << reacPerSec[i] << " ; " << seedArray[i] << endl;
        sumReacExe += reacExe[i];
        sumReacPerSec += reacPerSec[i];
    }
    bashOutput << "Average: " << sumReacExe / numSimulations << "; Average: " << sumReacPerSec / numSimulations << "; " << endl;
    bashOutput.close();
    seedArray.clear();
    reacPerSec.clear();
    reacExe.clear();
}
void menu(Model *model, double &initialTime, double &maximumTime, long int &seed, string &op)
{
    string filename;
    char printOp;
    clearScreen();
    //prints the menu
    cout << "--------------------------------------------" << endl;
    cout << "------------------STOCSIM-------------------" << endl;
    cout << "----A SOFTWARE FOR STOCHASTIC SIMULATION----" << endl;
    cout << "--------------------------------------------" << endl;
    if (!model->isModelLoaded())
    {
        //load a new model if there is any other loaded
        cout << "Insert the file's path and name (with the extension):" << endl;
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
    cout << "Insert the maximum time:" << endl;
    cin >> maximumTime;
    cout << "Methods:\nDM - Direct Method\nSDM - Sorting Direct Method\nODM - Optimized Direct Method\nFRM - First Reaction Method\nNRM - Next Reaction Method\nNRMC - Next Reaction Method Compact\nMNRM - Modified Next Reaction Method\nSNRM - Simplified Next Reaction Method\nRM - Rejection Method\n"
         << endl;

    double flag = true;
    while (flag)
    {
        cout << "Insert the Method:" << endl;
        cin >> op;
        if (op != "DM" && op != "SDM" && op != "ODM" && op != "FRM" && op != "NRM" && op != "NRMC" && op != "MNRM" && op != "SNRM" && op != "RM")
        {
            cout << "Error. Invalid operation!" << endl;
            op = "error";
        }
        else
            flag = false;
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
void clearScreen()
{
    //clear the screen
    if (PLATFORM_NAME == "windows")
        system("cls");
    else if (PLATFORM_NAME == "linux")
        system("clear");
}
void sleepFor(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000); // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef _WIN32
    Sleep(sleepMs);
#endif
}