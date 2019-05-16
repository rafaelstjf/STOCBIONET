#include "Log.hpp"
Log::Log(int size, map<string, long int> specNameNumber)
{
    this->specNameNumber = specNameNumber;
    first = nullptr;
    numNodes = 0;
    last = nullptr;
    this->size = size;
    currentArray = new int[size];
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
void Log::insertNode(double time, int *array)
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

    int val;
    Node *it = first;
    int* tempArray = new int[size];
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
    int* tempArray = new int[size];
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
void Log::setReacPerSecond(double reacPerSecond)
{
    this->reacPerSecond = reacPerSecond;
}
double Log::getReacPerSecond()
{
    return reacPerSecond;
}
void Log::saveDetailsToFile(string filename, unsigned long int seed)
{
    fstream outputFile;
    try
    {
        outputFile.open(filename, fstream::out | fstream::trunc);
        outputFile << "Number of reactions executed: " << reacCount << '\n';
        outputFile << "Reactions per second: " << reacPerSecond << '\n';
        outputFile << "Seed: " << seed << '\n';
        outputFile.close();
    }
    catch (const std::exception &e)
    {
        cout << "Impossible to save the file!" << endl;
    }
}
void Log::saveResultsToFile(string filename)
{
    fstream outputFile;
    try
    {
        outputFile.open(filename, fstream::out | fstream::trunc);
        int val;
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
            it = it->getNext();
        }
        outputFile.close();
    }
    catch (const std::exception &e)
    {
        cout << "Impossible to save the file!" << endl;
    }
}