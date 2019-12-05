#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <map>
#include <climits>

using namespace std;

class Node {
    private:
    map<int, int> dict;
    Node* next;
    Node* previous;
    long double time;

    public:
    Node();
    ~Node();
    Node* getNext();
    void setNext(Node* next);
    Node* getPrevious();
    void setPrevious(Node* previous);
    long double getTime();
    void setTime(long double time);
    map<int, int> getDict();
    int getValIndex(int index);
    int getValIndexFather(int index);
    void insertSpecie(int index, int value, int* array);
    bool checkExists(int index);
};
#endif
