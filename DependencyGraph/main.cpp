#include <iostream>
#include "DependencyGraph.h"
using namespace std;

int main()
{

        int p[7][5] = {
    0,0,0,0,1,
    0,0,0,0,0,
    1,0,0,0,0,
    0,1,0,0,0,
    0,0,1,0,0,
    0,0,1,0,0,
    0,0,0,1,0
    };
     int r[7][5] = {
    1,0,0,0,0,
    1,1,0,0,0,
    0,1,0,0,0,
    0,0,1,0,0,
    0,0,1,0,1,
    0,0,0,1,0,
    0,0,0,0,1
    };
     int** re= new int*[7];
    int** pr = new int*[7];

    for(int i = 0; i<7; i++)
    {
        re[i] = r[i];
        pr[i] = p[i];
    }
    DependencyGraph *dg = new DependencyGraph(5, re, pr, 7);
    dg->printGraph();

    //delete dg;
    return 0;
}
