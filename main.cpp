#include <iostream>
#include "DependencyGraph.h"
#include "SSA.h"
#include "DirectMethod.h"
using namespace std;

int main(int argc, char *argv[])
{
    SSA* s = new DirectMethod();
<<<<<<< HEAD
    s->perform("exemplo2.txt", 100.0);
=======
    s->perform("Entrada2.txt", 400.0);
>>>>>>> c543737a23a288a06c5fb728460e3a21c497ed21
    return 0;
}
