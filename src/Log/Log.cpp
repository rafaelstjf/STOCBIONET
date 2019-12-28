#include "Log.hpp"
Log::Log(int size, map<string, long int> specNameNumber)
{
    this->specNameNumber = specNameNumber;
    first = nullptr;
    numNodes = 0;
    last = nullptr;
    this->size = size;
    currentArray = new double[size];
}
Log::~Log()
{
    Node *it = first;
    Node *aux = nullptr;
    while (it != nullptr)
    {
        aux = it->getNext();
        delete it;
        it = aux;
    }
    delete it;
    delete aux;
}
void Log::insertNode(long double time, double *array)
{
    //increase the number of nodes, create a new node and insert the species
    numNodes++;
    Node *n = new Node();
    n->setTime(time);
    if (first == nullptr)
        first = n;
    else
        last->setNext(n);
    n->setPrevious(last);
    n->setNext(nullptr);
    last = n;
    for (int i = 0; i < size; i++)
    {
        n->insertSpecie(i, array[i], currentArray);
    }
}
void Log::printLog()
{
    //print all the nodes using the array to update the different species

    double val;
    Node *it = first;
    double *tempArray = new double[size];
    while (it != nullptr)
    {
        cout << "time: " << it->getTime() << endl;
        for (int i = 0; i < size; i++)
        {
            if (it->checkExists(i))
            {
                val = it->getValIndex(i);
                cout << val;
                tempArray[i] = val;
            }
            else
            {
                cout << tempArray[i];
            }
            if (i < size - 1)
                cout << ": ";
        }
        cout << endl;
        it = it->getNext();
    }
    delete[] tempArray;
}
stringstream Log::exportToStringStream()
{
    //exports the log into a stringstream
    int *tempArray = new int[size];
    stringstream buffer;
    int val;
    Node *it = first;
    while (it != nullptr)
    {
        buffer << it->getTime() << "; ";
        for (int i = 0; i < size; i++)
        {
            if (it->checkExists(i))
            {
                val = it->getValIndex(i);
                buffer << val;
                tempArray[i] = val;
            }
            else
            {
                buffer << tempArray[i];
            }
            if (i < size - 1)
                buffer << "; ";
        }
        buffer << '\n';
        it = it->getNext();
    }
    delete[] tempArray;
    return buffer;
}
void Log::setNumberReacExecuted(int reacCount)
{
    this->reacCount = reacCount;
}
int Log::getNumberReacExecuted()
{
    return reacCount;
}
void Log::setReacPerSecond(long double reacPerSecond)
{
    this->reacPerSecond = reacPerSecond;
}
void Log::setTimeSpent(long double timeSpent)
{
    this->timeSpent = timeSpent;
}
long double Log::getReacPerSecond()
{
    return reacPerSecond;
}
long double Log::getTimeSpent()
{
    return timeSpent;
}
void Log::saveDetailsToFile(string filename, unsigned long int seed)
{
    Utils *ut = new Utils();
    fstream outputFile;
    try
    {
        string newFileName = ut->checkIfFileExists(filename, ".txt");
        cout << "SAVING SIMULATION DETAILS IN " << newFileName << endl;
        outputFile.open(newFileName, fstream::out);
        outputFile << "Number of executed reactions: " << reacCount << '\n';
        outputFile << "Time spent on simulation: " << timeSpent << '\n';
        if (isinf(reacPerSecond))
            outputFile << "Reactions per milisecond: " << (long double)reacCount / (timeSpent / 1000) << '\n';
        else
            outputFile << "Reactions per second: " << reacPerSecond << '\n';
        outputFile << "Seed: " << seed << '\n';
        outputFile.close();
    }
    catch (const std::exception &e)
    {
        cout << "Impossible to save the file!" << endl;
    }
    delete ut;
}
void Log::saveResultsToFile(string filename)
{
    Utils *ut = new Utils();
    fstream outputFile;
    char op;
    try
    {
        string newFileName = ut->checkIfFileExists(filename, ".csv");
        if (numNodes > 5000)
        {
            cout << "There are is a large amount of data (" << numNodes << " lines). Do you want to save a reduced version? [y|n]" << endl;
            cin >> op;
        }
        cout << "SAVING SIMULATION RESULTS IN " << newFileName << endl;
        outputFile.open(newFileName, fstream::out | fstream::trunc);
        double val;
        Node *it = first;
        map<string, long int>::iterator itSpecies = specNameNumber.begin();
        string names[specNameNumber.size()];
        while (itSpecies != specNameNumber.end())
        {
            names[itSpecies->second] = itSpecies->first;
            itSpecies++;
        }
        outputFile << "Time; ";
        for (int i = 0; i < specNameNumber.size(); i++)
        {
            outputFile << names[i];
            if (i < specNameNumber.size() - 1)
                outputFile << "; ";
        }
        outputFile << '\n';
        while (it != nullptr)
        {
            outputFile << it->getTime() << "; ";
            for (int i = 0; i < size; i++)
            {
                if (it->checkExists(i))
                {
                    val = it->getValIndex(i);
                    outputFile << val;
                    currentArray[i] = val;
                }
                else
                {
                    outputFile << currentArray[i];
                }
                if (i < size - 1)
                    outputFile << "; ";
            }
            outputFile << '\n';
            if (op == 'y')
            {
                long int space = numNodes / 5000;
                for (long int k = 0; k < space; k++)
                    if (it)
                        it = it->getNext();
            }
            else
            {

                it = it->getNext();
            }
        }
        outputFile.close();
    }
    catch (const std::exception &e)
    {
        cout << "Impossible to save the file!" << endl;
    }
    delete ut;
}