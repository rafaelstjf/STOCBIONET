#include <iostream>
#include "DirectMethod.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    DirectMethod* dm = new DirectMethod();
    dm->perform("BIOMD0000000001.xml");
    return 0;
}
