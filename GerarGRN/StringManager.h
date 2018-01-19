#ifndef STRINGMANAGER_H
#define STRINGMANAGER_H

#include <iostream>
#include <string>

using namespace std;
class StringManager
{
    public:
        StringManager();
        virtual ~StringManager();
        string replaceString(string str, string r1, string r2);
        const vector<string> explode(const string& s, const char& c);
    protected:

    private:
};

#endif // STRINGMANAGER_H
