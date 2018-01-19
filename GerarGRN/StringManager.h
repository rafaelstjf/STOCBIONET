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
    protected:

    private:
};

#endif // STRINGMANAGER_H
