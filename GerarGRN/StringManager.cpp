#include "StringManager.h"

StringManager::StringManager()
{
    //ctor
}

StringManager::~StringManager()
{
    //dtor
}
string StringManager::replaceString(string str, string r1, string r2){
 string outputString;
    int rIndex = 0;
    int nextIndex = 0;
    for(int i = 0; i<str.length(); i++)
    {
        if(str[i]==r1[0])
        {
            rIndex = 0;
            while(str[i]==r1[rIndex])
            {
                if(rIndex==r1.length()-1)
                    break;
                if(i==str.length()-1)
                    break;
                else{
                i++;
                rIndex++;
                }
            }
            if(rIndex == r1.length()-1){ //substring matches
                for(int j = 0; j<r2.length(); j++){
                    char c = r2[j];
                    outputString.append(1,c);
                }
            }else{
                for(int j = i-rIndex-2; j == i; j++){
                    char c = r2[j];
                    outputString.append(1, c);
                }
                if(i==str.length()-1)
                    outputString.append(1,str[i]);
                rIndex = 0;
            }
        }
        else{
            outputString.append(1,str[i]);
        }
    }
    return outputString;
}
const vector<string> StringManager::explode(const string& s, const char& c)
{
    //source: http://www.cplusplus.com/articles/2wA0RXSz/
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}