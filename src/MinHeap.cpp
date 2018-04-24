#include "../include/MinHeap.hpp"
void swap(double *x, double *y)
{
    double temp = *x;
    *x = *y;
    *y = temp;
}
MinHeap::MinHeap(int capacity)
{
    heapSize = 0;
    this->capacity = capacity;
    harr = new double[capacity];
}
int MinHeap::parent(int i)
{
    return ((i - 1) / 2);
}
int MinHeap::left(int i)
{
    return (2 * i + 1);
}
int MinHeap::right(int i)
{
    return (2 * i + 2);
}
void MinHeap::insertKey(double val)
{
    if (heapSize < capacity)
    {
        //insert the new key at the end
        heapSize++;
        int i = heapSize - 1;
        harr[i] = val;
        //fix the min heap property if it's violated
        while (i != 0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }
}
double MinHeap::extractMin()
{
    if (heapSize <= 0)
        return INT_MAX;
    if (heapSize == 1)
    {
        heapSize--;
        return harr[0];
    }
    //store the minimum value and remove it from the heap
    double root = harr[0];
    harr[0] = harr[heapSize - 1];
    heapSize--;
    minHeapify(0);
    return root;
}
void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}
void MinHeap::minHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heapSize && harr[l] < harr[i])
        smallest = l;
    if (r < heapSize && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        minHeapify(smallest);
    }
}
void MinHeap::decreaseKey(int i, double newVal)
{
    harr[i] = newVal;
    while(i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}
