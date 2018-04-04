#include <iostream>
#include "DependencyGraph.h"
//#include "SSA.h"
#include "DirectMethod.h"
using namespace std;

int main(int argc, char *argv[])
{
    SSA* s = new DirectMethod();
    s->perform("Entrada3.txt", 500.0);
    //delete s;
    return 0;
}
