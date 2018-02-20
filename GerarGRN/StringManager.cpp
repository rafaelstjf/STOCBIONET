#include "StringManager.h"

StringManager::StringManager()
{
    //ctor
}

StringManager::~StringManager()
{
    //dtor
}
string StringManager::replaceChar(string& str, char c1, char c2)
{
    string outputString;
    for(int i = 0; i< str.size(); i++)
    {
        if(str[i] == c1)
            outputString.append(1, c2);
        else
            outputString.append(1, str[i]);
    }
    return outputString;
}
string StringManager::replaceString(string& str, string r1, string r2)
{
    string outputString;
    int rIndex = 0;
    int nextIndex = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == r1[0])
        {
            rIndex = 0;
            while (str[i] == r1[rIndex])
            {
                if (rIndex == r1.length() - 1)
                    break;
                if (i == str.length() - 1)
                    break;
                else
                {
                    i++;
                    rIndex++;
                }
            }
            if (rIndex == r1.length() - 1)
            {
                //substring matches
                for (int j = 0; j < r2.length(); j++)
                {
                    char c = r2[j];
                    outputString.append(1, c);
                }
            }
            else
            {
                for (int j = i - rIndex - 2; j == i; j++)
                {
                    char c = r2[j];
                    outputString.append(1, c);
                }
                if (i == str.length() - 1)
                    outputString.append(1, str[i]);
                rIndex = 0;
            }
        }
        else
        {
            outputString.append(1, str[i]);
        }
    }
    return outputString;
}
const vector<string> StringManager::explodeChar(const string &s, const char &c)
{
    //source: http://www.cplusplus.com/articles/2wA0RXSz/
    string buff;
    vector<string> v;
    for(int i = 0; i<s.size(); i++)
    {
        char n = s[i];
        if (n != c)
            buff += n;
        else if (n == c && buff != "")
        {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(buff);

    return v;
}
string StringManager::trim(string str)
{
    string output;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
            output.append(1, str[i]);
    }
    return output;
}

const vector<string> StringManager::multExplodeChar(const string &s, const char &c1, const char &c2)
{
    vector<string> v = explodeChar(s, c1);
    vector<string> v2;
    string buff;
    for (int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j< v[i].size(); j++)
        {
            char n = v[i][j];
            if (v[i][j] != c2)
                buff += v[i];
            else if (v[i][j] == c2 && buff != "")
            {
                v2.push_back(buff);
                buff = "";
            }
        }
        if (buff != "")
            v2.push_back(buff);
        buff = "";
    }
    return v2;
}
const vector<string> StringManager::explodeString(const string &str, const string &s1)
{
    string buffer;
    vector<string> v;
    for(int i = 0; i< str.size(); i++)
    {
        if(str[i]==s1[0])
        {
            int tempI = i;
            while(str[tempI] == s1[(tempI-i)] && (tempI - i) < s1.size()){
                tempI++;
            }
            if(tempI == s1[s1.size()-1]){
                v.push_back(buffer);
                buffer = "";
            }
            else{
                buffer.append(1,str[i]);
                i++;
            }
        }
        else
        {
            buffer.append(1,str[i]);
        }
    }
    v.push_back(buffer);
    return v;
}
const vector<string> StringManager::multExplodeString(const string &str, const string &s1, const string &s2){
    vector<string> v1 = explodeString(str, s1);
    vector<string> v2;
    string buffer;
    for(int i = 0; i < v1.size(); i++){
        for(int j = 0; j < v1[i].size(); j++){
            if(v1[i][j] == s2[0]){
                int tempJ = j;
                 while(v1[i][tempJ] == s2[(tempJ-j)] && (tempJ - j) < s2.size()){
                tempJ++;
            }
            if(tempJ == s2[s2.size()-1]){
                v2.push_back(buffer);
                buffer = "";
            }
            else{
                buffer.append(1,v1[i][j]);
                i++;
            }
            }
            v2.push_back(buffer);
            buffer = "";
        }
    return v2;
}
}
bool StringManager::isdigit(char c){
    if(c >= 48 && c <= 57)
        return true;
    else
        return false;
}
