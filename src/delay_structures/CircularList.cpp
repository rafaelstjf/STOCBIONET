#include "CircularList.hpp"

CircularList::CircularList(int capacity)
{
    this->capacity = capacity;
    inUse = 0;
    //creates an array with "capacity" positions
    array = new DelayNode *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        array[i] = nullptr;
    }
    first = -1;
    last = -1;
}
CircularList::~CircularList()
{
    for (int i = 0; i < capacity; i++)
    {
        delete array[i];
    }
    delete[] array;
}
void CircularList::insertKey(int specIndex, int reacIndex, double delayTime)
{

    //resize the array
    if (inUse == capacity)
    {
        //array is full
        int newCapacity = 2 * capacity;
        DelayNode **temp = new DelayNode *[newCapacity];
        //imports all the elements and then puts nullptr in the others
        for (int i = 0; i < newCapacity; i++)
        {
            temp[i] = nullptr;
        }
        int it = first;
        int it2 = 0;
        int count = 0;
        while(count < inUse){
            if(array[it]){
                temp[it2] = array[it];
                it2++;
            }
            it = (it+1) % capacity;
            count++;
        }
        capacity = newCapacity;
        array = temp;
        first = 0;
        last = it2-1;
    }
    //insert the element
    int index = 0;
    if (first == -1) //empty array
    {
        //increase the first index to 0
        index = 0;
        first = 0;
        last = 0;
    }
    else if (delayTime <= array[first]->getDelayTime())
    {
        first = (first - 1 < 0) ? capacity - 1 : ((first - 1) % capacity);
        index = first;
    }
    //bigger than the last
    else if (delayTime >= array[last]->getDelayTime())
    {
        //increase the last index
        last = (last + 1) % capacity;
        index = last;
    }
    //it's bigger than the first and lower than the last
    else
    {
        //it goes anti-clockwise and stops when the new element is smaller than the current
        int i = last;
        int count = 0;
        while (i != first && count < inUse)
        {
            array[(i + 1) % capacity] = array[i];
            if (delayTime <= array[i]->getDelayTime())
                break; //found position
            else i = (i - 1 < 0) ? capacity - 1 : ((i - 1) % capacity);
            count++;
        }
        index = i;
        last = (last + 1) % capacity;
    }
    DelayNode *n = new DelayNode(specIndex, reacIndex, delayTime);
    array[index] = n;
    inUse++;
}

void CircularList::removeFirst()
{
    delete array[first];
    array[first] = nullptr;
    if (last == first)
    {
        //if it has only one element
        first = -1;
        last = -1;
    }
    else
        first = (first + 1) % capacity;
    inUse--;
}
void CircularList::removeByIndexRange(vector<int> indexes)
{
}
void CircularList::removeByIndex(int index)
{
}
void CircularList::print()
{
    int index = first;
    int count = 0;
    while (count < inUse)
    {
        if (array[index] != nullptr)
            cout << "Index: " << index << " Delay: " << array[index]->getDelayTime() << " SpecIndex: " << array[index]->getSpecIndex() << " ReacIndex: " << array[index]->getReacIndex() << endl;
        else
            cout << "Index: " << index << " NULL" << endl;
        index = (index + 1) % capacity;
        count++;
    }
}
bool CircularList::isEmpty()
{
    if (inUse == 0)
        return true;
    else
        return false;
}
int CircularList::getFirstIndex()
{
    return first;
}
int CircularList::getLastIndex()
{
    return last;
}
int CircularList::getCapacity()
{
    return capacity;
}
DelayNode *CircularList::getNode(int index)
{
    return array[index];
}
vector<DelayNode *> CircularList::extractEqualFirst()
{
    //it searches for the value in the whole array, adds it on the vector and removes from the array
    vector<DelayNode *> tempArray;
    double value;
    if (array[first] == nullptr)
        return tempArray;
    else
        value = getMinNode()->getDelayTime();
    DelayNode *n;
    int count = 0;
    int i = first;
    while (count < inUse)
    {
        if (array[i] != nullptr)
        {
            if (array[i]->getDelayTime() >= value - EP && array[i]->getDelayTime() <= value + EP)
            {
                n = new DelayNode(array[i]->getSpecIndex(), array[i]->getReacIndex(), array[i]->getDelayTime());
                tempArray.push_back(n);
            }
            count++;
        }
        i = (i + 1) % capacity;
    }
    for(int k = 0; k < tempArray.size(); k++)
        removeFirst();
    return tempArray;
}
DelayNode *CircularList::getMinNode()
{
    //it returns the first element of the array
    if (first == -1)
        return nullptr;
    else
        return array[first];
}