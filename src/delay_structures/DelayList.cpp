#include "DelayList.hpp"
DelayList::DelayList()
{
    inUse = 0;
}
DelayList::~DelayList()
{
    // for (DelayNode* obj : array)
    // if(obj) delete obj;
    array.clear();
}
void DelayList::insertKey(int specIndex, int reacIndex, double delayTime)
{
    //cout << delayTime << " " << inUse << endl;
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
            vector<DelayNode*>::iterator it{array.data() + index};
            array.insert(it, n);
        }
    }
    inUse++;
}
void DelayList::removeByIndex(int arrayIndex)
{
}
void DelayList::removeByIndexRange(int arrayIndexBeg, int arrayIndexEnd)
{
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

    vector<DelayNode *> tempArray;
    double value;
    if (array.size() == 0)
        return tempArray;
    else
    {
        value = array[0]->getDelayTime();
    }
    int indexesToRemove = 0;
    unsigned int i = 0;
    while (i < inUse)
    {
        if (array[i]->getDelayTime() >= value - EP && array[i]->getDelayTime() <= value + EP)
        {
            DelayNode *n;
            n = new DelayNode(array[i]->getSpecIndex(), array[i]->getReacIndex(), array[i]->getDelayTime());
            tempArray.push_back(n);
            indexesToRemove++;
        }
        i++;
    }
    //cout << "inuse before: " << inUse;
    inUse = inUse - indexesToRemove;
    //cout << " InUse now: " << inUse << endl;;
    // for(int j = 0; j < indexesToRemove; j++){
    //     array[j] = nullptr;
    // }
    vector<DelayNode*>::iterator it{array.data() + indexesToRemove};
    array.erase(array.begin(), it);
    return tempArray;
}
DelayNode *DelayList::getMinNode()
{
    if (inUse == 0)
        return nullptr;
    else
        return array[0];
}
void DelayList::print()
{
    for (unsigned int i = 0; i < array.size(); i++)
    {
        cout << "Index: " << i << " Delay" << array[i]->getDelayTime() << " SpecIndex: " << array[i]->getSpecIndex() << " ReacIndex: " << array[i]->getReacIndex() << endl;
    }
}