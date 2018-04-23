#ifndef STRINGMANAGER_HPP
#define STRINGMANAGER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class StringManager
{
    public:
        StringManager();
        virtual ~StringManager();
        string replaceString(string &str, string r1, string r2);
        string replaceChar(string &str, char c1, char c2);
        const vector<string> explodeChar(const string& s, const char& c);
        const vector<string> multExplodeChar(const string &s, const char &c1, const char &c2);
        const vector<string> explodeString(const string &str, const string &s1);
        const vector<string> multExplodeString(const string &str, const string &s1, const string &s2);
        string trim(string str);
        bool isdigit(char c);
    protected:

    private:
};

#endif // STRINGMANAGER_H
