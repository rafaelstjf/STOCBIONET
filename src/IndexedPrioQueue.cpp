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
void IndexedPrioQueue::minHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heapsize && heapArray[l]->getTime() < heapArray[i]->getTime())
        smallest = l;
    if (r < heapsize && heapArray[r]->getTime() < heapArray[smallest]->getTime())
        if (smallest != i)
        {
            swap(i, smallest);
            minHeapify(smallest);
        }
}
void IndexedPrioQueue::insertKey(int index, double time)
{
    if (heapsize == capacity)
        return;
    cout << "Inserting: " << index << "; " << time << endl;
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
        int flag = 0;
        if(l >= 0 && r >=0 && l < heapsize && r < heapsize)
        {
            smallest = l;
            if (heapArray[l]->getTime() > heapArray[r]->getTime())
                smallest = r;
        }
        else if(l >=0 && l < heapsize)
        {
            smallest = l;
            flag = 1;
        }
        else if(r >=0 && r < heapsize)
        {
            smallest = r;
            flag = 2;
        }
        if((flag==1 || flag == 2) &&(heapArray[index]->getTime() > heapArray[smallest]->getTime()))
        {
            swap(index, smallest);
            updateAux(smallest);
        }
    }
}
void IndexedPrioQueue::printQueue()
{
    for(int i = 0; i < heapsize; i++)
    {
        /*cout << "Current node: " << heapArray[i]->getIndex() << " | " << heapArray[i]->getTime() <<endl;
        if(i>=1)cout << "Parent: " << heapArray[parent(i)]->getIndex() << " | " << heapArray[parent(i)]->getTime() <<endl;
        if(left(i) >= 0 && left(i) < heapsize)cout << "Left child: " << heapArray[left(i)]->getIndex() << " | " << heapArray[left(i)]->getTime() <<endl;
        if(right(i) >= 0 && right(i) < heapsize)cout << "Right child: " << heapArray[right(i)]->getIndex() << " | " << heapArray[right(i)]->getTime() <<endl;
        */
        cout << "(" << heapArray[i]->getIndex() << " ; " << heapArray[i]->getTime() << ")";;
    }
}
HeapNode* IndexedPrioQueue::getNode(int index)
{
    return heapArray[indexArray[index]];
}
