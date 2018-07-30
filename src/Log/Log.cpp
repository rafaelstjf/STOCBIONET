#include "../../include/Log/Log.hpp"

Log::Log(int size)
{
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
    int val;
    Node *it = first;
    while (it != nullptr)
    {
        cout << "time: " << it->getTime() << endl;
        for (int i = 0; i < size; i++)
        {
            if (it->checkExists(i))
            {
                val = it->getValIndex(i);
                cout << val;
                currentArray[i] = val;
            }
            else
            {
                cout << currentArray[i];
            }
            if (i < size - 1)
                cout << ": ";
        }
        cout << endl;
        it = it->getNext();
    }
}
stringstream Log::exportToStringStream()
{
    //exports the log into a string, if the number of nodes is bigger than the maximum, the algorithm
    //will jump some nodes
    stringstream buffer;
    int val;
    Node *it = first;
    if (numNodes >= 5000)
    {
        int jump = ceil((double)numNodes / 5000);
        int j = jump;
        while (it != nullptr)
        {
            if (j == jump)
            {
                buffer << it->getTime() << "; ";
                for (int i = 0; i < size; i++)
                {
                    if (it->checkExists(i))
                    {
                        val = it->getValIndex(i);
                        buffer << val;
                        currentArray[i] = val;
                    }
                    else
                    {
                        buffer << currentArray[i];
                    }
                    if (i < size - 1)
                        buffer << "; ";
                }
                buffer << '\n';
                j = 1;
            }
            else
            {
                for (int i = 0; i < size; i++)
                {
                    if (it->checkExists(i))
                    {
                        val = it->getValIndex(i);
                        currentArray[i] = val;
                    }
                }
                j++;
            }
            it = it->getNext();
        }
    }
    else
    {
        while (it != nullptr)
        {
            buffer << it->getTime() << "; ";
            for (int i = 0; i < size; i++)
            {
                if (it->checkExists(i))
                {
                    val = it->getValIndex(i);
                    buffer << val;
                    currentArray[i] = val;
                }
                else
                {
                    buffer << currentArray[i];
                }
                if (i < size - 1)
                    buffer << "; ";
            }
            buffer << '\n';
            it = it->getNext();
        }
    }
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
