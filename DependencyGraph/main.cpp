#include <iostream>
#include "DependencyGraph.h"
using namespace std;

int main()
{

    int r[5][7]=
    {
        1,1,0,0,0,0,0,
        0,1,1,0,0,0,0,
        0,0,0,1,1,0,0,
        0,0,0,0,0,1,0,
        0,0,0,0,1,0,1
    };
    int p[5][7]=
    {
        0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,
        0,0,0,0,1,1,0,
        0,0,0,0,0,0,1,
        1,0,0,0,0,0,0
    };
    int** re= new int*[5];
    int** pr = new int*[5];

    for(int i = 0; i<5; i++)
    {
        re[i] = r[i];
        pr[i] = p[i];
    }
    DependencyGraph *dg = new DependencyGraph(5, re, pr, 7);
    dg->printGraph();

    //delete dg;
    return 0;
}
