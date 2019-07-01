#include "DelayList.hpp"
DelayList::DelayList()
{
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
    array.push_back(n);
    sortList();
}
void DelayList::sortList()
{
    //insertion sort
    unsigned int i, j;
    DelayNode *chosed;
    for (i = 1; i < array.size(); i++)
    {
        chosed = array[i];
        j = i - 1;
        while ((j >= 0) && (array[j]->getDelayTime() > chosed->getDelayTime()))
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = chosed;
    }
}
void DelayList::removeByIndex(int arrayIndex)
{
    //it uses the default vector's function to remove an element
    delete array[arrayIndex];
    if (arrayIndex < array.size())
        array.erase(array.begin() + arrayIndex);
}
void DelayList::removeByIndexRange(int arrayIndexBeg, int arrayIndexEnd)
{
    //it uses the default vector's function to remove an element
    int it = arrayIndexBeg;
    while (it <= arrayIndexEnd)
    {
        delete array[it];
        it++;
    }
    if (arrayIndexBeg == arrayIndexEnd)
        array.erase(array.begin() + arrayIndexBeg);
    else
        array.erase(array.begin() + arrayIndexBeg, array.begin() + arrayIndexEnd + 1);
}
DelayNode *DelayList::getNode(int index)
{
    return array[index];
}
int DelayList::getArraySize()
{
    return array.size();
}
vector<DelayNode *> DelayList::extractEqual(double value)
{

    DelayNode *n;
    vector<DelayNode *> tempArray;
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