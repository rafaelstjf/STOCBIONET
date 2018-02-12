#include <iostream>
//#include "TReact.h"
#include "StringManager.h"
#include <string>
#include <vector>
using namespace std;

int main()
{
    StringManager* sm = new StringManager();
    string batata = "A batata -> esta ->assando";
    vector<string> teste = sm->explodeString(batata, "->");
    cout << "Hello world!" << endl;
    for(int i = 0; i< teste.size(); i++){
        cout << teste[i] << endl;
    }
    return 0;
}
