#include <iostream>
#include "DependencyGraph.hpp"
//#include "SSA.h"
#include "DirectMethod.hpp"
#include "FirstReactionMethod.hpp"
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
