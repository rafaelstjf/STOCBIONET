#include "../include/IndexedPrioQueue.hpp"

IndexedPrioQueue::IndexedPrioQueue(int capacity)
{
    this->capacity = capacity;
    heapArray = new HeapNode[capacity];
    indexArray = new int[capacity];
    heapsize = 0;
}
IndexedPrioQueue::~IndexedPrioQueue()
{
    delete[] heapArray;
    delete[] indexArray;
}
int IndexedPrioQueue::left(int i)
{
    return (2 * i + 1);
}
int IndexedPrioQueue::right(int i)
{
    return (2 * i + 2)
}
int IndexedPrioQueue::parent(int i)
{
    return (i - 1) / 2;
}
void swap(HeapNode *x, HeapNode *y, int ix, int iy)
{
    HeapNode *temp = x;
    x = y;
    y = temp;
    indexArray[x->getIndex] = iy;
    indexArray[y->getIndex] = ix;
}
void IndexedPrioQueue::minHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heapsize && heapArray[l].getTime() < heapArray[i].getTime())
        smallest = l;
    if (r < heapsize && heapArray[r].getTime() < heapArray[smallest].getTime())
        if (smallest != i)
        {
            swap(&harr[i], &harr[smallest], i, smallest);
            minHeapify(smallest);
        }
}
void IndexedPrioQueue::insertKey(int index, double time)
{
    if (heapsize == capacity)
        return;
    heapsize++;
    int i = heapSize - 1;
    heapArray[i] = new HeapNode(index, time);
    indexArray[index] = i;
    while (i != 0 && heapArray[parent(i)].getTime() > heapArray[i].getTime())
    {
        swap(&heapArray[i], &heapArray[parent(i)], i, parent(i));
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
void IndexedPrioQueue::update(int index, double time)
{
    heapArray[indexArray[index]]->setTime(time);
    updateAux(indexArray[index]);
}
void IndexedPrioQueue::updateAux(int index)
{
    int p = parent(index);
    if (heapArray[index]->getTime() < heapArray[p]->getTime())
    {
        swap(&heapArray[index], &heapArray[p], index, p);
        updateAux(p);
    }
    else
    {
        int l = left(index);
        int r = right(index);
        int smallest = l;
        if (heapArray[l]->getTime() > heapArray[r] - getTime())
            smallest = r;
        if (heapArray[index]->getTime() > heapArray[smallest] - getTime())
        {
            swap(&heapArray[index], &heapArray[smallest], index, smallest);
            updateAux(smallest);
        }
    }
}