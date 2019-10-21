#include "DelayList.hpp"
DelayList::DelayList()
{
    inUse = 0;
}
DelayList::~DelayList()
{
    for (unsigned int i = 0; i < array.size(); i++)
    {
        delete array[i];
    }
    array.clear();
}
void DelayList::insertKey(int specIndex, int reacIndex, double delayTime)
{
    DelayNode *n = new DelayNode(specIndex, reacIndex, delayTime);
    if (inUse == 0)
        array.push_back(n);
    else
    {
        int index = -1;
        for (int i = 0; i < inUse; i++)
        {
            if (delayTime <= array[i]->getDelayTime())
            {
                index = i;
                break;
            }
        }
        if (index == -1)
            array.push_back(n);
        else
        {

            DelayNode *lastElement = array[inUse - 1];
            for (int i = index + 1; i < inUse; i++)
            {
                array[i] = array[i - 1];
            }
            array.push_back(lastElement);
            array[index] = n;
        }
    }
    inUse++;
}
void DelayList::removeByIndex(int arrayIndex)
{
    //it uses the default vector's function to remove an element
    delete array[arrayIndex];
    inUse--;
    if (arrayIndex < array.size())
        array.erase(array.begin() + arrayIndex);
}
void DelayList::removeByIndexRange(int arrayIndexBeg, int arrayIndexEnd)
{
    //it uses the default vector's function to remove an element
    int it = arrayIndexEnd;
    while (it >= arrayIndexBeg)
    {
        delete array[it];
        it--;
        array.erase(array.begin() + arrayIndexBeg);
        inUse--;
    }
}
DelayNode *DelayList::getNode(int index)
{
    return array[index];
}
int DelayList::getArraySize()
{
    return array.size();
}
vector<DelayNode *> DelayList::extractEqualFirst()
{

    DelayNode *n;
    vector<DelayNode *> tempArray;
    double value;
    if (array.size() == 0)
        return tempArray;
    else
    {
        value = array[0]->getDelayTime();
    }
    vector<int> indexesToRemove;
    unsigned int i = 0;
    while (i < array.size())
    {
        if (array[i]->getDelayTime() >= value - EP && array[i]->getDelayTime() <= value + EP)
        {
            n = new DelayNode(array[i]->getSpecIndex(), array[i]->getReacIndex(), array[i]->getDelayTime());
            tempArray.push_back(n);
            indexesToRemove.push_back(i);
        }
        i++;
    }
    inUse = inUse - indexesToRemove.size();
    removeByIndexRange(indexesToRemove[0], indexesToRemove[indexesToRemove.size() - 1]);
    indexesToRemove.clear();
    return tempArray;
}
DelayNode *DelayList::getMinNode()
{
    if (array.size() == 0)
        return nullptr;
    else
        return array.front();
}
void DelayList::print()
{
    for (unsigned int i = 0; i < array.size(); i++)
    {
        cout << "Index: " << i << " Delay" << array[i]->getDelayTime() << " SpecIndex: " << array[i]->getSpecIndex() << " ReacIndex: " << array[i]->getReacIndex() << endl;
    }
}