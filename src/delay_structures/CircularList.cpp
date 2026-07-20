#include "CircularList.hpp"

CircularList::CircularList(int capacity)
{
    this->capacity = capacity > 0 ? capacity : 1;
    inUse = 0;
    //creates an array with "capacity" positions
    array = new DelayNode *[this->capacity];
    for (int i = 0; i < this->capacity; i++)
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
    if (capacity <= 0)
        capacity = 1;
    if (inUse == capacity)
    {
        int oldCapacity = capacity;
        DelayNode **oldArray = array;
        capacity = 2 * capacity;
        array = new DelayNode *[capacity];
        for (int i = 0; i < capacity; i++)
            array[i] = nullptr;
        for (int count = 0, idx = first; count < inUse; count++, idx = (idx + 1) % oldCapacity)
            array[count] = oldArray[idx];
        delete[] oldArray;
        first = 0;
        last = inUse - 1;
    }

    vector<DelayNode *> ordered;
    ordered.reserve(inUse + 1);
    for (int count = 0, idx = first; count < inUse; count++, idx = (idx + 1) % capacity)
        ordered.push_back(array[idx]);

    DelayNode *node = new DelayNode(specIndex, reacIndex, delayTime);
    vector<DelayNode *>::iterator insertAt = ordered.begin();
    while (insertAt != ordered.end() && (*insertAt)->getDelayTime() <= delayTime)
        ++insertAt;
    ordered.insert(insertAt, node);

    for (int i = 0; i < capacity; i++)
        array[i] = nullptr;
    for (unsigned int i = 0; i < ordered.size(); i++)
        array[i] = ordered[i];
    inUse = ordered.size();
    first = 0;
    last = inUse - 1;
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
    vector<DelayNode *> tempArray;
    DelayNode *minNode = getMinNode();
    if (minNode == nullptr)
        return tempArray;

    double value = minNode->getDelayTime();
    while (inUse > 0 && array[first] != nullptr &&
           array[first]->getDelayTime() >= value - DELAY_EP &&
           array[first]->getDelayTime() <= value + DELAY_EP)
    {
        tempArray.push_back(array[first]);
        array[first] = nullptr;
        if (last == first)
        {
            first = -1;
            last = -1;
        }
        else
        {
            first = (first + 1) % capacity;
        }
        inUse--;
    }
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