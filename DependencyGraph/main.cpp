#include <iostream>
#include "DependencyGraph.h"
using namespace std;

int main()
{
/*Example 1
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
*/
int r[6][6]{
    1,0,0,0,0,0,
    0,1,0,0,0,0,
    0,0,1,0,0,0,
    0,0,1,0,0,0,
    0,0,0,1,0,1,
    0,0,0,0,1,0
};
int p[6][6]{
    0,0,0,0,1,0,
    1,0,0,0,0,1,
    0,1,0,0,0,0,
    0,0,0,0,0,0,
    0,0,1,1,0,0,
    0,0,0,1,0,0
};
 int** re= new int*[6];
    int** pr = new int*[6];

    for(int i = 0; i<6; i++)
    {
        re[i] = r[i];
        pr[i] = p[i];
    }
    DependencyGraph *dg = new DependencyGraph(6, re, pr, 6);
    dg->printGraph();

    //delete dg;
    return 0;
}
