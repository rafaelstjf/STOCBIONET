#include <iostream>
#include "DependencyGraph.h"
#include "SSA.h"
#include "DirectMethod.h"
using namespace std;

int main(int argc, char *argv[])
{
    SSA* s = new DirectMethod();
    s->perform("exemplo.txt", 10.0);
    return 0;
}
