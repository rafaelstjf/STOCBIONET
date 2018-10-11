#ifndef LOG_HPP
#define LOG_HPP

#include<sstream>
#include "Node.hpp"
#include <iostream>
#include <climits>
#include <math.h>
using namespace std;
class Log{

    private:
    Node* first;
    Node* last;
    int size;
    unsigned int numNodes;
    double reacPerSecond;
    int reacCount;
    int* currentArray;
    public:
    Log(int size);
    ~Log();
    void insertNode(double time, int* array);
    void printLog();
    stringstream exportToStringStream();
    void setReacPerSecond(double reacPerSecond);
    double getReacPerSecond();
    void setNumberReacExecuted(int reacCount);
    int getNumberReacExecuted();

};

#endif