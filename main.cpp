#include <iostream>
#include "DirectMethod.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    DirectMethod* dm = new DirectMethod();
    dm->perform("Models/BIOMD0000000625.xml");
    return 0;
}
