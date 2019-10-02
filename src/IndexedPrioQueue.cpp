#include "IndexedPrioQueue.hpp"

IndexedPrioQueue::IndexedPrioQueue(int capacity)
{
    this->capacity = capacity;
    heapArray = new HeapNode *[capacity];
    indexArray = new int[capacity];
    for (int i = 0; i < capacity; i++)
    {
        heapArray[i] = nullptr;
        indexArray[i] = -1;
    }
    heapsize = 0;
}
IndexedPrioQueue::~IndexedPrioQueue()
{
    for (int i = 0; i < capacity; i++)
    {
        delete heapArray[i];
    }
    delete[] heapArray;
    delete[] indexArray;
}
int IndexedPrioQueue::left(int i)
{
    return ((2 * i) + 1);
}
int IndexedPrioQueue::right(int i)
{
    return ((2 * i) + 2);
}
int IndexedPrioQueue::parent(int i)
{
    return (i - 1) / 2;
}
void IndexedPrioQueue::swap(int ix, int iy)
{
    HeapNode *temp = heapArray[ix];
    heapArray[ix] = heapArray[iy];
    indexArray[temp->getIndex()] = iy;
    indexArray[heapArray[iy]->getIndex()] = ix;
    heapArray[iy] = temp;
}
void IndexedPrioQueue::insertKey(int index, double time)
{
    if (heapsize == capacity)
        return;
    int i = heapsize;
    heapsize++;
    HeapNode *n = new HeapNode(index, time);
    heapArray[i] = n;
    indexArray[index] = i;
    while (i != 0 && heapArray[parent(i)]->getTime() > heapArray[i]->getTime())
    {
        swap(i, parent(i));
        i = parent(i);
    }
}
HeapNode *IndexedPrioQueue::getMin()
{
    if (heapsize == 0)
        return nullptr;
    else
        return heapArray[0];
}
void IndexedPrioQueue::update(int reacIndex, double time)
{
    heapArray[indexArray[reacIndex]]->setTime(time);
    updateAux(indexArray[reacIndex]);
}
void IndexedPrioQueue::updateAux(int index)
{
    int p = parent(index);
    if (index > 0 && heapArray[index]->getTime() < heapArray[p]->getTime())
    {
        swap(index, p);
        updateAux(p);
    }
    else
    {
        int l = left(index);
        int r = right(index);
        int smallest = index;
        if (l < heapsize && r < heapsize)
        {
            if (heapArray[l]->getTime() > heapArray[r]->getTime())
                smallest = r;
            else
                smallest = l;
        }
        else if (l >= heapsize && r < heapsize)
            smallest = r;
        else if (r >= heapsize && l < heapsize)
            smallest = l;
        if (smallest != index && (heapArray[index]->getTime() > heapArray[smallest]->getTime()))
        {
            swap(index, smallest);
            updateAux(smallest);
        }
    }
}
void IndexedPrioQueue::print()
{
    for (int i = 0; i < heapsize; i++)
    {
        cout << "(" << heapArray[i]->getIndex() << " ; " << heapArray[i]->getTime() << ")";
    }
    cout << endl;
}
HeapNode *IndexedPrioQueue::getNode(int index)
{
    return heapArray[indexArray[index]];
}
