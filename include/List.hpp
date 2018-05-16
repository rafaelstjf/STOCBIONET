#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "../include/HeapNode.hpp"
using namespace std;

class List{
public:
    List(int c);
    ~List();
    HeapNode* getMin();
    void insertKey(int index, double time);
    void update(int index, double time);
    bool isSort();
    void print();
    HeapNode* getNode(int index);
private:
    int capacity;
    int inUse;
    int* arrayIndex;
    HeapNode** arr;
    void sort();
    void swap(int i, int j);

};

#endif
