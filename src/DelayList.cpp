#include "../include/DelayList.hpp"
DelayList::DelayList()
{
}
DelayList::~DelayList()
{
    array.clear();
}
void DelayList::insert(int specIndex, int reacIndex, double delayTime)
{
    Node n;
    n.specIndex = specIndex;
    n.reacIndex = reacIndex;
    n.delayTime = delayTime;
    array.push_back(n);
    sortList();
}
void DelayList::sortList()
{
    int i, j;
    Node chosed;
    for (i = 1; i < array.size(); i++)
    {
        chosed = array[i];
        j = i - 1;
        while ((j >= 0) && (array[j].delayTime > chosed.delayTime))
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = chosed;
    }
}
void DelayList::removeBySpecie(int specIndex)
{
    int i = 0;
    while (i < array.size())
    {
        if (array[i].specIndex == specIndex)
            break;
        i++;
    }
    if (i < array.size())
        array.erase(array.begin() + i);
}
void DelayList::removeByArrayIndex(int arrayIndex)
{
    if (arrayIndex < array.size())
        array.erase(array.begin() + arrayIndex);
}
double DelayList::getDelayTime(int index)
{
    if (index < array.size())
        return array[index].delayTime;
}
int DelayList::getSpecIndex(int index)
{
    if (index < array.size())
        return array[index].specIndex;
}
int DelayList::getReacIndex(int index)
{
    if (index < array.size())
        return array[index].reacIndex;
}
int DelayList::getArraySize()
{
    return array.size();
}