#include <iostream>
#include "DirectMethod.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    DirectMethod* dm = new DirectMethod();
    dm->perform("Models/BIOMD0000000001_SBML-L2V3.xml");
    return 0;
}
