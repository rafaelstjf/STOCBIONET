#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
   map<int, string> teste;
teste[1] = "a";
teste[2] = "c";
teste[3] = "d";
teste[4] = "e";
teste[5] = "f";
teste.insert(make_pair(1, "b"));
map<int, string>::iterator it = teste.begin();
while(it != teste.end())
{
    cout << it->first << " : " << it->second << endl << endl;
    it++;

}

}
