#include "../../include/delay_structures/DelayList.hpp"
DelayList::DelayList()
{
}
DelayList::~DelayList()
{
    for (int i = 0; i < array.size(); i++)
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
    int i, j;
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
    if (arrayIndex < array.size())
        array.erase(array.begin() + arrayIndex);
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
    for (int i = 0; i < array.size(); i++)
    {
        if (array[i]->getDelayTime() >= value - INT_MIN && array[i]->getDelayTime() <= value + INT_MIN)
        {
            n = new DelayNode(array[i]->getSpecIndex(), array[i]->getReacIndex(), array[i]->getDelayTime());
            tempArray.push_back(n);
        }
        removeByIndex(i);
        i--;
    }
    return tempArray;
}
DelayNode *DelayList::getMinNode()
{
    if (array.size() == 0)
        return nullptr;
    else
        return array[0];
}
void DelayList::print()
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << "Index: " << i << " Delay" << array[i]->getDelayTime() << " SpecIndex: " << array[i]->getSpecIndex() << " ReacIndex: " << array[i]->getReacIndex() << endl;
    }
}