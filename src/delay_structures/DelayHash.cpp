#include "DelayHash.hpp"

DelayHash::DelayHash(int capacity, double low, double high, double **delaysValue, int reacNumber, int specNumber)
{

    lowestDelay = delaysValue[0][0];
    biggestDelay = delaysValue[0][0];
    this->capacity = biggestDelay;
    this->precision = 100000;
    for (int i = 0; i < specNumber; i++)
    {
        for (int j = 0; j < reacNumber; j++)
        {
            if (biggestDelay < delaysValue[i][j])
                biggestDelay = delaysValue[i][j];
            if (lowestDelay > delaysValue[i][j])
                lowestDelay = delaysValue[i][j];
        }
    }
    Table *table1 = new Table;
    Table *table2 = new Table;
    table1->low = 0;
    table1->high = biggestDelay;
    table1->inUse = 0;
    table2->inUse = 0;
    table2->low = biggestDelay;
    table2->high = 2 * biggestDelay;
    table2->array = new RingBuffer *[capacity];
    table1->array = new RingBuffer *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        table1->array[i] = new RingBuffer(10);
        table2->array[i] = new RingBuffer(10);
    }
    firstIndex = INT_MAX;
    firstDelay = INT_MAX;
    firstTable = 1;
}
DelayHash::~DelayHash()
{

    for (int i = 0; i < capacity; i++)
    {
        delete table1->array[i];
        delete table2->array[i];
    }
    delete[] table1->array;
    delete[] table2->array;
    delete table1;
    delete table2;
}
void DelayHash::insertKey(int specIndex, int reacIndex, double delayTime)
{
    int choosedTable = 1;
    int index = 1;
    if (delayTime <= table1->high)
    {
        index = hashingFunction(delayTime, table1->low, table1->high);
        table1->array[index]->insertKey(specIndex, reacIndex, delayTime);
        table1->inUse++;
    }
    else
    {
        index = hashingFunction(delayTime, table2->low, table2->high);
        table2->array[index]->insertKey(specIndex, reacIndex, delayTime);
        choosedTable = 2;
        table2->inUse++;
    }
    if (delayTime < firstDelay)
    {
        firstDelay = delayTime;
        firstIndex = index;
        firstTable = choosedTable;
    }
}

void DelayHash::print()
{
    for (int i = 0; i < capacity; i++)
    {
        cout << "Node: " << i << endl;
        cout << "Table 1:" << endl;
        table1->array[i]->print();
        cout << "Table 2:" << endl;
        table2->array[i]->print();
    }
}
int DelayHash::hashingFunction(double delayTime, int low, int high)
{

    //R = inf + ((sup-inf)/(1.0/precision))*int
    //1.0/precision if precision = 0.0....
    int key = ceil((delayTime - low) * (precision / (high - low)));
    cout << "DELAY: " << delayTime << " KEY: " << key << " key% c: " << key % capacity << " c: " << capacity << endl;
    return key % capacity;
}
bool DelayHash::isEmpty()
{
    if (table1->inUse == 0 && table2->inUse == 0)
        return true;
    else
        return false;
}
DelayNode *DelayHash::getMinNode()
{
    if (isEmpty())
        return nullptr;
    else if (firstTable == 1)
        return table1->array[firstIndex]->getMinNode();
    else
        return table2->array[firstIndex]->getMinNode();
}
vector<DelayNode *> DelayHash::extractEqual(double value)
{
    int index;
    int choosedTable = 1;
    bool updateTable = false;
    if (value <= table1->high && value < table2->high)
        choosedTable = 1;
    else if (value <= table1->high && value > table2->high)
    {
        choosedTable = 1;
        updateTable = true;
    }
    else if (value > table1->high && value <= table2->high)
    {
        choosedTable = 2;
        updateTable = true;
    }
    vector<DelayNode *> vec;
    if (choosedTable == 1)
    {
        index = hashingFunction(value, table1->low, table1->high);
        if (!table1->array[index]->isEmpty())
        {
            vec = table1->array[index]->extractEqual(value);
        }
        table1->inUse = table1->inUse - vec.size();
        if (table1->inUse != 0 && updateTable)
        {
            int ind = firstIndex;
            while (table1->array[ind]->getMinNode() == nullptr)
            {
                ind++;
            }
            firstIndex = ind;
            firstDelay = table1->array[ind]->getMinNode()->getDelayTime();
        }
        else if (table1->inUse == 0 && updateTable)
        {
            firstIndex = INT_MAX;
            firstDelay = INT_MAX;
            firstTable = 1;
        }
        else if (table1->inUse == 0 && !updateTable)
        {
            if (table2->inUse != 0)
            {
                int ind = 0;
                while (table2->array[ind]->getMinNode() == nullptr)
                {
                    ind++;
                }
                firstIndex = ind;
                firstDelay = table2->array[ind]->getMinNode()->getDelayTime();
                firstTable = 2;
            }
        }
        if (updateTable)
        {
            table2->low = table1->high;
            table2->high = table2->high + biggestDelay;
        }
    }
    else
    {
        index = hashingFunction(value, table2->low, table2->high);
        if (!table2->array[index]->isEmpty())
        {
            vec = table2->array[index]->extractEqual(value);
        }
        table2->inUse = table2->inUse - vec.size();
        if (table2->inUse != 0 && updateTable)
        {
            int ind = firstIndex;
            while (table2->array[ind]->getMinNode() == nullptr)
            {
                ind++;
            }
            firstIndex = ind;
            firstDelay = table2->array[ind]->getMinNode()->getDelayTime();
        }
        else if (table2->inUse == 0 && updateTable)
        {
            firstIndex = INT_MAX;
            firstDelay = INT_MAX;
            firstTable = 1;
        }
        else if (table2->inUse == 0 && !updateTable)
        {
            if (table1->inUse != 0)
            {
                int ind = 0;
                while (table1->array[ind]->getMinNode() == nullptr)
                {
                    ind++;
                }
                firstIndex = ind;
                firstDelay = table1->array[ind]->getMinNode()->getDelayTime();
                firstTable = 1;
            }
        }
        if (updateTable)
        {
            table1->low = table2->high;
            table1->high = table1->high + biggestDelay;
        }
    }
    return vec;
}