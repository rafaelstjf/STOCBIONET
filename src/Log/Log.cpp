#include "../include/log/Log.hpp"

Log::Log(int size)
{
    first = nullptr;
    last = nullptr;
    this->size = size;
    currentArray = new int[size];
}
Log::~Log()
{
    Node* it = first;
    Node* aux = nullptr;
    while(it!=nullptr)
    {
        aux = it->getNext();
        delete it;
        it = aux;
    }
    delete it;
    delete aux;
}
void Log::insertNode(double time, int array[])
{
    Node* n = new Node();
    n->setTime(time);
    if(first == nullptr)
        first = n;
    else
        last->setNext(n);
    n->setPrevious(last);
    n->setNext(nullptr);
    last = n;
    for(int i = 0; i < size; i++)
    {
        n->insertSpecie(i, array[i], currentArray);
    }
}
void Log::printLog()
{
    int val;
    Node* it = first;
    while(it!=nullptr)
    {
        cout << "time: " << it->getTime() << endl;
        for(int i = 0; i < size; i++)
        {
            if(it->checkExists(i))
            {
                val = it->getValIndex(i);
                cout << val;
                currentArray[i] = val;
            }
            else
            {
                cout << currentArray[i];
            }
            if(i < size-1)
                cout<< ": ";
        }
        cout << endl;
        it = it->getNext();
    }
}
stringstream Log::exportToStringStream()
{
    stringstream buffer;
    int val;
    Node* it = first;
    while(it!=nullptr)
    {
        buffer << it->getTime() << "; ";
        for(int i = 0; i < size; i++)
        {
            if(it->checkExists(i))
            {
                val = it->getValIndex(i);
                buffer << val;
                currentArray[i] = val;
            }
            else
            {
                buffer << currentArray[i];
            }
            if(i < size-1)
                buffer<< "; ";
        }
        buffer << '\n';
        it = it->getNext();
    }
    return buffer;
}
