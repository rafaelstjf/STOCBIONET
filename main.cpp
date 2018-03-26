#include <iostream>
#include "DependencyGraph.h"
#include "SSA.h"
#include "DirectMethod.h"
using namespace std;

int main(int argc, char *argv[])
{
    SSA* s = new DirectMethod();
    s->perform("exemplo2.txt", 100.0);
    return 0;
}
