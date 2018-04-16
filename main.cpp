#include <iostream>
#include "DependencyGraph.h"
//#include "SSA.h"
#include "DirectMethod.h"
#include "FirstReactionMethod.h"
using namespace std;

int main(int argc, char *argv[])
{
    SSA* s = new DirectMethod();
    SSA* s2 = new FirstReactionMethod();
    s->perform("Entrada3.txt", 400.0);
    s2->perform("Entrada3.txt", 400.0);
    //delete s;
    return 0;
}
