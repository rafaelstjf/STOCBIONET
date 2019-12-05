#ifndef LOG_HPP
#define LOG_HPP

#include<sstream>
#include "Node.hpp"
#include <iostream>
#include <climits>
#include <math.h>
#include <fstream>
#include <map>
#include "../Utils.hpp"
using namespace std;
class Log{

    private:
    Node* first;
    Node* last;
    int size;
    unsigned int numNodes;
    double reacPerSecond;
    int reacCount;
    long double timeSpent;
    int* currentArray;
    map<string, long int>specNameNumber; //name and index nof the species 
    public:
    Log(int size, map<string, long int>specNameNumber);
    ~Log();
    void insertNode(long double time, int* array);
    void printLog();
    stringstream exportToStringStream();
    void saveResultsToFile(string filename);
    void saveDetailsToFile(string filename, unsigned long int seed);
    void setReacPerSecond(long double reacPerSecond);
    void setTimeSpent(long double timeSpent);
    long double getTimeSpent();
    long double getReacPerSecond();
    void setNumberReacExecuted(int reacCount);
    int getNumberReacExecuted();

};

#endif
