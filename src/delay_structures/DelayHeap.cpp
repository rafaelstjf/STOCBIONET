#include "DelayHeap.hpp"
DelayHeap::DelayHeap(int capacity)
{
    this->capacity = capacity;
    heapSize = 0;
    array = new DelayNode *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        array[i] = nullptr;
    }
}
DelayHeap::~DelayHeap()
{
    for (int i = 0; i < capacity; i++)
    {
        delete array[i];
    }
    delete[] array;
}
int DelayHeap::parent(int i)
{
    return (i - 1) / 2;
}

int DelayHeap::left(int i)
{
    return (2 * i + 1);
}
int DelayHeap::right(int i)
{
    return (2 * i + 2);
}
void DelayHeap::insertKey(int specIndex, int reacIndex, double delayTime)
{
    if (heapSize == capacity)
    {
        //resize the heap
        DelayNode **temp = array;
        array = new DelayNode *[2 * capacity];
        for (int i = 0; i < capacity; i++)
        {
            array[i] = temp[i];
        }
        for (int i = capacity; i < 2 * capacity; i++)
        {
            array[i] = nullptr;
        }
        capacity = 2 * capacity;
        delete[] temp;
    }
    heapSize++;
    int i = heapSize - 1;
    DelayNode *n = new DelayNode(specIndex, reacIndex, delayTime);
    array[i] = n;
    while (i != 0 && array[parent(i)] != nullptr && array[parent(i)]->getDelayTime() > array[i]->getDelayTime())
    {
        swap(array[i], array[parent(i)]);
        i = parent(i);
    }
}
void DelayHeap::decreaseKey(int i, int specIndex, double delayTime, int reacIndex)
{
    array[i]->setSpecIndex(specIndex);
    array[i]->setDelayTime(delayTime);
    array[i]->setReacIndex(reacIndex);
    while (i != 0 && array[parent(i)]->getDelayTime() > array[i]->getDelayTime())
    {
        swap(array[i], array[parent(i)]);
        i = parent(i);
    }
}
DelayNode *DelayHeap::extractMin()
{
    if (heapSize <= 0)
        return nullptr;
    if (heapSize == 1)
    {
        heapSize--;
        DelayNode *extracted = array[0];
        array[0] = nullptr;
        return extracted;
    }
    DelayNode *root = array[0];
    array[0] = array[heapSize - 1];
    array[heapSize - 1] = nullptr;
    heapSize--;
    minHeapify(0);
    return root;
}
void DelayHeap::deleteKey(int i)
{
    decreaseKey(i, array[i]->getSpecIndex(), (double)INT_MIN, array[i]->getReacIndex());
    delete extractMin();
}
void DelayHeap::minHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heapSize && array[l]->getDelayTime() < array[i]->getDelayTime())
        smallest = l;
    if (r < heapSize && array[r]->getDelayTime() < array[smallest]->getDelayTime())
        smallest = r;
    if (smallest != i)
    {
        swap(array[i], array[smallest]);
        minHeapify(smallest);
    }
}
vector<DelayNode *> DelayHeap::extractEqualFirst()
{

    DelayNode *n;
    vector<DelayNode *> tempArray;
    double value;
    if (getMinNode() == nullptr)
        return tempArray;
    else
    {
        value = getMinNode()->getDelayTime();
    }
    while (array[0] != nullptr && array[0]->getDelayTime() >= value - EP && array[0]->getDelayTime() <= value + EP)
    {
        //cout << "Batata: " << value << endl;
        n = new DelayNode(array[0]->getSpecIndex(), array[0]->getReacIndex(), array[0]->getDelayTime());
        tempArray.push_back(n);
        DelayNode *r = extractMin();
        if (r != nullptr)
            delete r;
    }
    return tempArray;
}
DelayNode *DelayHeap::getMinNode()
{
    if (heapSize == 0)
        return nullptr;
    else
        return array[0];
}
void DelayHeap::print()
{
    for (int i = 0; i < heapSize; i++)
    {
        for (int j = 0; j < pow(2, i) && pow(2, i) < capacity; j++)
        {
            if (array[(int)(j + pow(2, i) - 1)] != nullptr)
                cout << array[(int)(j + pow(2, i) - 1)]->getDelayTime() << " ";
        }
        cout << endl;
    }
}
bool DelayHeap::isHeap()
{
    for (int i = 0; i < (heapSize - 2) / 2; i++)
    {
        if (array[2 * i + 1]->getDelayTime() < array[i]->getDelayTime())
            return false;
        if (2 * i + 2 < heapSize && array[2 * i + 2]->getDelayTime() < array[i]->getDelayTime())
            return false;
    }
    return true;
}