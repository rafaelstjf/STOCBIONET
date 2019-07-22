#include "DelayHash.hpp"

DelayHash::DelayHash(double **delaysValue, int reacNumber, int specNumber)
{

    //Get the biggest delay
    biggestDelay = delaysValue[0][0];
    for (int i = 0; i < specNumber; i++)
    {
        for (int j = 0; j < reacNumber; j++)
        {
            if (biggestDelay < delaysValue[i][j])
                biggestDelay = delaysValue[i][j];
        }
    }
    precision = 100000;
    capacity = reacNumber;
    table1 = new Table;
    table2 = new Table;
    /*
    *   Table 1  = from 0 to Biggest delay
    *   Table 2 = from Biggest delay to 2 * Biggest delay
    */
    table1->low = 0;
    table1->high = biggestDelay;
    table2->low = biggestDelay;
    table2->high = 2 * biggestDelay;
    table1->inUse = 0;
    table2->inUse = 0;
    firstIndex = INT_MAX;
    firstDelay = INT_MAX;
    firstTable = 1;
    for (int i = 0; i < capacity; i++)
    {
        RingBuffer *r1 = new RingBuffer(10);
        RingBuffer *r2 = new RingBuffer(10);
        table1->array.push_back(r1);
        table2->array.push_back(r2);
    }
}
DelayHash::~DelayHash()
{

    for (int i = 0; i < capacity; i++)
    {
        delete table1->array[i];
        delete table2->array[i];
    }
    table1->array.clear();
    table2->array.clear();
    delete table1;
    delete table2;
}
void DelayHash::insertKey(int specIndex, int reacIndex, double delayTime)
{
    int choosedTable = 1;
    int index = 0;
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
    cout << "Table 1:" << endl;
    for (int i = 0; i < capacity; i++)
    {
        cout << " * Node: " << i << endl;
        table1->array[i]->print();
    }
    cout << "Table 2:" << endl;
    for (int i = 0; i < capacity; i++)
    {
        cout << " * Node: " << i << endl;
        table2->array[i]->print();
    }
}
int DelayHash::hashingFunction(double delayTime, double low, double high)
{

    //R = inf + ((sup-inf)/(1.0/precision))*int
    //1.0/precision if precision = 0.0....
    int key = ceil((delayTime - low) * (precision / (high - low)));
    //cout << "LOW: " << low << " High: " << high << " key: " << key << " delayTime: " << delayTime << endl;
    return key % capacity;
}
bool DelayHash::isEmpty()
{
    if (table1->inUse == 0 && table2->inUse == 0)
    {
        return true;
    }
    else
        return false;
}
DelayNode *DelayHash::getMinNode()
{
    
    cout << "First Index: " << firstIndex << " First Table: " << firstTable << " First Value: " << firstDelay << endl;
    cout << "Table 1 - low: " << table1->low << " Table 1 - High: " << table1->high << " InUse: " << table1->inUse << endl;
    cout << "Table 2 - low: " << table2->low << " Table 2 - High: " << table2->high << " InUse: " << table2->inUse << endl;
    if (isEmpty())
        return nullptr;
    else if (firstTable == 1)
    {
        //cout << "MinNODE: " << table1->array[firstIndex]->getMinNode()->getDelayTime() << endl;
        return table1->array[firstIndex]->getMinNode();
    }
    else
    {
        //cout << "MinNODE: " << table2->array[firstIndex]->getMinNode()->getDelayTime() << endl;
        return table2->array[firstIndex]->getMinNode();
    }
}
vector<DelayNode *> DelayHash::extractEqualFirst()
{
    double value;
    vector<DelayNode *> vec;
    if (isEmpty())
        return vec; //returns an empty vector
    else
    {
        value = firstDelay;
    }
    //out << "Extracting " << value << endl;
    int index;
    int choosedTable = 0;
    bool updateTable = false;
    if (value > table1->low && value <= table1->high)
    {
        choosedTable = 1;
        if (value > table2->high) //table 1 is newer than table 2
            updateTable = true;
    }
    else if (value <= table2->high)
    {
        //table 2 is newer than table 1
        choosedTable = 2;
        updateTable = true;
    }
    if (choosedTable == 1)
    {
        vec = table1->array[firstIndex]->extractEqualFirst();
        table1->inUse = table1->inUse - vec.size();
        if (table1->inUse != 0)
        {
            //case 1: there are elements on the first table and the second one is older
            firstIndex = INT_MAX;
            firstDelay = INT_MAX;
            firstTable = 1;
            for (unsigned int i = 0; i < table1->array.size(); i++)
            {
                if (table1->array[i]->getMinNode() != nullptr && table1->array[i]->getMinNode()->getDelayTime() < firstDelay)
                {
                    firstIndex = i;
                    firstDelay = table1->array[i]->getMinNode()->getDelayTime();
                }
            }
        }
        else
        {
            //case 2: there aren't elements on the first table and the second one is older
            if (updateTable)
            {

                firstIndex = INT_MAX;
                firstDelay = INT_MAX;
                firstTable = 1;
            }
            else
            {
                //case 3: there aren't elements on the first table and the second one is newer

                if (table2->inUse != 0)
                {
                    firstIndex = INT_MAX;
                    firstDelay = INT_MAX;
                    firstTable = 2;
                    for (unsigned int i = 0; i < table2->array.size(); i++)
                    {
                        if (table2->array[i]->getMinNode() != nullptr && table2->array[i]->getMinNode()->getDelayTime() < firstDelay)
                        {
                            firstIndex = i;
                            firstDelay = table2->array[i]->getMinNode()->getDelayTime();
                        }
                    }
                }
                else
                {
                    firstIndex = INT_MAX;
                    firstDelay = INT_MAX;
                    firstTable = 1;
                }
            }
        }
        //updates table 2
        if (updateTable)
        {
            table2->low = table1->high;
            table2->high = table2->low + biggestDelay;
        }
    }
    else
    {
        vec = table2->array[firstIndex]->extractEqualFirst();
        table2->inUse = table2->inUse - vec.size();
        if (table2->inUse != 0)
        {

            //case 1: there are elements on the second table and the first one is older
            firstIndex = INT_MAX;
            firstDelay = INT_MAX;
            firstTable = 2;
            for (unsigned int i = 0; i < table2->array.size(); i++)
            {
                if (table2->array[i]->getMinNode() != nullptr && table2->array[i]->getMinNode()->getDelayTime() < firstDelay)
                {
                    firstIndex = i;
                    firstDelay = table2->array[i]->getMinNode()->getDelayTime();
                }
            }
        }
        else
        {
            if (updateTable)
            {
                //case 2: there aren't elements on the second table and the first one is older
                firstIndex = INT_MAX;
                firstDelay = INT_MAX;
                firstTable = 1;
            }
            else
            {
                //case 3: there aren't elements on the second table and the first one is newer
                if (table1->inUse != 0)
                {
                    firstIndex = INT_MAX;
                    firstDelay = INT_MAX;
                    firstTable = 1;
                    for (unsigned int i = 0; i < table1->array.size(); i++)
                    {
                        if (table1->array[i]->getMinNode() != nullptr && table1->array[i]->getMinNode()->getDelayTime() < firstDelay)
                        {
                            firstIndex = i;
                            firstDelay = table1->array[i]->getMinNode()->getDelayTime();
                        }
                    }
                }
                else
                {
                    firstIndex = INT_MAX;
                    firstDelay = INT_MAX;
                    firstTable = 2;
                }
            }
        }
        if (updateTable)
        {
            table1->low = table2->high;
            table1->high = table1->low + biggestDelay;
        }
    }
    return vec;
}