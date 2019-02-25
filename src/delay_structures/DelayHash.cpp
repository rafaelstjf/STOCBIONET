#include "DelayHash.hpp"

DelayHash::DelayHash(int capacity, double low, double high, double precision)
{
    this->low = low;
    this->high = high;
    this->precision = precision;
    this->capacity = capacity;
    inUse = 0;
    firstIndex = INT_MAX;
    firstDelay = INT_MAX;
    array = new RingBuffer *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        array[i] = new RingBuffer(10);
    }
}
DelayHash::~DelayHash()
{
    for (int i = 0; i < capacity; i++)
    {
        delete array[i];
    }
    delete[] array;
}
void DelayHash::insertKey(int specIndex, int reacIndex, double delayTime)
{
    int index = hashingFunction(delayTime);
    array[index]->insertKey(specIndex, reacIndex, delayTime);
    if (delayTime < firstDelay)
    {
        firstDelay = delayTime;
        firstIndex = index;
    }
    inUse++;
}

void DelayHash::print()
{
    for (int i = 0; i < capacity; i++)
    {
        cout << "Node: " << i << endl;
        array[i]->print();
    }
}
int DelayHash::hashingFunction(double delayTime)
{

    /*
    int whole = floor(delayTime);
    int decimal = floor((delayTime - whole) * 100);
    return (decimal + whole) % capacity;
    */
    //R = inf + ((sup-inf)/(1.0/precision))*int
    int key = (delayTime - low) * ((1.0 /  precision)/(high - (1+low)));
    return key % capacity;
}
bool DelayHash::isEmpty()
{
    if (inUse == 0)
        return true;
    else
        return false;
}
DelayNode *DelayHash::getMinNode()
{
    if (inUse == 0)
        return nullptr;
    else
        return array[firstIndex]->getMinNode();
}
vector<DelayNode *> DelayHash::extractEqual(double value)
{
    vector<DelayNode *> vec, vec2;
    int index = hashingFunction(value);
    if (!array[index]->isEmpty())
    {
        vec2 = array[index]->extractEqual(value);
        vec.reserve(vec.size() + vec2.size());
        vec.insert(vec.end(), vec2.begin(), vec2.end());
    }
    inUse = inUse - vec.size();
    if (inUse != 0)
    {
        bool first = true;
        for (int i = 0; i < capacity; i++)
        {
            if (!array[i]->isEmpty())
            {
                if (first)
                {
                    firstIndex = i;
                    firstDelay = array[i]->getMinNode()->getDelayTime();
                }
                else if (array[i]->getMinNode()->getDelayTime() < firstDelay)
                {
                    firstDelay = array[i]->getMinNode()->getDelayTime();
                    firstIndex = i;
                }
            }
        }
    }
    return vec;
}