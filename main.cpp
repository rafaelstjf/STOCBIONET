#include <iostream>
#include "DependencyGraph.h"
#include "DirectMethod.h"
using namespace std;

int main(int argc, char *argv[])
{
    int** r = new int*[5];
    int** p = new int*[5];
    for(int i = 0; i< 5; i++){
        r[i] = new int[7];
        p[i] = new int[7];
    }
    int r1[5][7] = {1,1,0,0,0,0,0,
         0,1,1,0,0,0,0,
         0,0,0,1,1,0,0,
         0,0,0,0,0,1,0,
         0,0,0,0,1,0,1
    };

    int p1[5][7] = {0,0,1,0,0,0,0,
         0,0,0,1,0,0,0,
         0,0,0,0,1,1,0,
         0,0,0,1,0,0,1,
         1,0,0,0,0,0,0
    };
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 7; j++){
            r[i][j] = r1[i][j];
            p[i][j] = p1[i][j];
        }
    }
    DependencyGraph* dg = new DependencyGraph(5, r, p, 7);
    dg->printGraph();
    return 0;
}
