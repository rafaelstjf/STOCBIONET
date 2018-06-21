#ifndef LOG_HPP
#define LOG_HPP

#include<sstream>
#include "Node.hpp"
#include <iostream>
#include <climits>
using namespace std;
class Log{

    private:
    Node* first;
    Node* last;
    int size;
    int* currentArray;
    public:
    Log(int size);
    ~Log();
    void insertNode(double time, int array[]);
    void printLog();
    stringstream exportToStringStream();

};

#endif
