#include "../include/IndexedPrioQueue.hpp"


IndexedPrioQueue::IndexedPrioQueue(int capacity)
{
    this->capacity = capacity;
    heapArray = new HeapNode*[capacity];
    indexArray = new int[capacity];
    heapsize = 0;
}
IndexedPrioQueue::~IndexedPrioQueue()
{
    for(int i = 0; i < capacity; i++){
        delete heapArray[i];
    }
    delete[] heapArray;
    delete[] indexArray;
}
int IndexedPrioQueue::left(int i)
{
    return (2 * i + 1);
}
int IndexedPrioQueue::right(int i)
{
    return (2 * i + 2);
}
int IndexedPrioQueue::parent(int i)
{
    return (i - 1) / 2;
}
void IndexedPrioQueue::swap(int ix, int iy)
{
    //x = temp
    int index = heapArray[ix]->getIndex();
    double time = heapArray[ix]->getTime();
    //x = y
    indexArray[heapArray[ix]->getIndex()] = iy;
    heapArray[ix]->setIndex(heapArray[iy]->getIndex());
    heapArray[ix]->setTime(heapArray[iy]->getTime());
    //y = x
    indexArray[heapArray[iy]->getIndex()] = ix;
    heapArray[iy]->setIndex(index);
    heapArray[iy]->setTime(time);
}
void IndexedPrioQueue::insertKey(int index, double time)
{
    if (heapsize == capacity)
        return;
    heapsize++;
    int i = heapsize - 1;
    HeapNode* n =  new HeapNode(index, time);
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
void IndexedPrioQueue::update(int index, double time)
{
    heapArray[indexArray[index]]->setTime(time);
    updateAux(indexArray[index]);
}
void IndexedPrioQueue::updateAux(int index)
{
    int p = parent(index);
    if (p >= 0  && heapArray[index]->getTime() < heapArray[p]->getTime())
    {
        swap(index, p);
        updateAux(p);
    }
    else
    {
        int l = left(index);
        int r = right(index);
        int smallest;
        bool flag = false;
        if(l >= 0 && r >=0 && l < heapsize && r < heapsize)
        {
            smallest = l;
            if (heapArray[l]->getTime() > heapArray[r]->getTime())
                smallest = r;
            flag = true;
        }
        else if(l >=0 && l < heapsize)
        {
            smallest = l;
            flag = true;
        }
        else if(r >=0 && r < heapsize)
        {
            smallest = r;
            flag = true;
        }
        if(flag &&(heapArray[index]->getTime() > heapArray[smallest]->getTime()))
        {
            swap(index, smallest);
            updateAux(smallest);
        }
    }
}
void IndexedPrioQueue::print()
{
    for(int i = 0; i < heapsize; i++)
    {
        cout << "(" << heapArray[i]->getIndex() << " ; " << heapArray[i]->getTime() << ")";;
    }
    cout << endl;
}
HeapNode* IndexedPrioQueue::getNode(int index)
{
    return heapArray[indexArray[index]];
}
