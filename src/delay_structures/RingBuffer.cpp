#include "RingBuffer.hpp"

RingBuffer::RingBuffer(int capacity)
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
RingBuffer::~RingBuffer()
{
    for (int i = 0; i < capacity; i++)
    {
        delete array[i];
    }
    delete[] array;
}
void RingBuffer::insertKey(int specIndex, int reacIndex, double delayTime)
{

    //resize the array
    if (inUse == capacity)
    {
        //array is full
        int newCapacity = 2 * capacity;
        DelayNode **temp = new DelayNode *[newCapacity];
        //imports all the elements and then puts nullptr in the others
        for (int i = 0; i <= capacity; i++)
        {
            temp[i] = array[i];
        }
        for (int i = last + 1; i < newCapacity; i++)
        {
            temp[i] = nullptr;
        }
        capacity = newCapacity;
        array = temp;
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
    //bigger than the last
    else if (delayTime > array[last]->getDelayTime())
    {
        //increase the last index
        last = (last + 1) % capacity;
        index = last;
    }
    //it's bigger than the first and lower than the last
    else
    {
        //it goes anti-clockwise and stops when the new element is smaller than the current
        int count = 0;
        int i = last;
        while (count < inUse)
        {
            if (array[i] != nullptr)
            {
                count++;
                if (delayTime <= array[i]->getDelayTime())
                    break; //found position
            }
            i = (i <= 0) ? capacity - 1 : ((i - 1) % capacity);
        }
        index = i;
        i = last;
        while (count > 0)
        {
            //it moves the elements from the last until the desirable index
            array[((i + 1) % capacity)] = array[i];
            i = (i <= 0) ? capacity - 1 : ((i - 1) % capacity);
            count--;
        }
        last = (last + 1) % capacity;
    }
    DelayNode *n = new DelayNode(specIndex, reacIndex, delayTime);
    array[index] = n;
    inUse++;
}

void RingBuffer::removeFirst()
{
    delete array[first];
    array[first] = nullptr;
    if (last == first)
        first = -1;
    else
        first = (first + 1) % capacity;
    inUse--;
}
void RingBuffer::removeByIndex(int index)
{
    if (index == first) //if it's the first so call removeFirst()
        removeFirst();
    else
    {
        //goes from the end to the beginning moving 1 position until gets in the desirable index
        delete array[index];
        array[index] = nullptr;
        if (index < last)
        {
            //if the index is lower than the last so goes from index to last increasing
            for (int i = index; i < last; i++)
            {
                array[i] = array[i + 1];
            }
            array[last] = nullptr;
            last = (last <= 0) ? capacity - 1 : ((last - 1) % capacity);
        }
        else if (index > last)
        {
            //if not so goes from index to last decreasing
            for (int i = index; i > last; i--)
            {
                array[i] = array[i - 1];
                if (i == first)
                    first = (first - 1) % capacity;
            }
            array[last] = nullptr;
            last = (last + 1) % capacity;
        }
        else
        {
            //index == last
            last = (last <= 0) ? capacity - 1 : ((last - 1) % capacity);
        }
        inUse--;
        if(inUse==0){
            last = -1;
            first = -1;
        }
    }
}
void RingBuffer::print()
{
    for (int i = 0; i < capacity; i++)
    {
        if (array[i] != nullptr)
            cout << "Index: " << i << " Delay: " << array[i]->getDelayTime() << " SpecIndex: " << array[i]->getSpecIndex() << " ReacIndex: " << array[i]->getReacIndex() << endl;
    }
}
bool RingBuffer::isEmpty()
{
    if (first == -1)
        return true;
    else
        return false;
}
int RingBuffer::getFirstIndex()
{
    return first;
}
int RingBuffer::getLastIndex()
{
    return last;
}
int RingBuffer::getCapacity()
{
    return capacity;
}
DelayNode *RingBuffer::getNode(int index)
{
    return array[index];
}
vector<DelayNode *> RingBuffer::extractEqual(double value)
{
    //it searches for the value in the whole array, adds it on the vector and removes from the array
    vector<DelayNode *> tempArray;
    DelayNode *n;
    int count = 0;
    int i = first;
    vector<int> indexesToRemove;
    while (count <= inUse)
    {
        if (array[i] != nullptr)
        {
            if (array[i]->getDelayTime() >= value - EP && array[i]->getDelayTime() <= value + EP)
            {
                n = new DelayNode(array[i]->getSpecIndex(), array[i]->getReacIndex(), array[i]->getDelayTime());
                tempArray.push_back(n);
                indexesToRemove.push_back(i);
            }
            count++;
            i = (i + 1) % capacity;
        }
        else //empty element
            i = (i + 1) % capacity;
    }
    for (int i = 0; i < indexesToRemove.size(); i++)
    {
        removeByIndex(indexesToRemove[i]);
    }
    return tempArray;
}
DelayNode *RingBuffer::getMinNode()
{
    //it returns the first element of the array
    if (first == -1)
        return nullptr;
    else
        return array[first];
}