#include <iostream>
#include "DirectMethod.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Hello world!" << endl;
        DirectMethod *dm = new DirectMethod();
        dm->perform("Models/BIOMD0000000001.xml");
    }
    else
    {
        cout << "Hello world!" << endl;
        DirectMethod *dm = new DirectMethod();
        dm->perform(argv[1]);
    }
    return 0;
}
