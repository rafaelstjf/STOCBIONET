#include "Utils.h"

Utils::Utils()
{
     fat[0] = 1;
     fat[1] = 1;
     fat[2] = 2;
     fat[3] = 6;
     fat[4] = 24;
     fat[5] = 120;
     fat[6] = 720;
     fat[7] = 5040;
     fat[8] = 40320;
     fat[9] = 362880;
     fat[10] = 3628800;


}
Utils::~Utils()
{
}

double Utils::getRandomNumber()
{
}
double Utils::binomialCoefficient(int k, int n)
{
    int fatn, fatk, fatnk;
    if (n > 10)
        fatn = calcFactorial(n);
    else
        fatn = fat[n];
    if (k > 10)
        fatk = calcFactorial(k);
    else
        fatk = fat[k];
    if (n - k > 10)
        fatnk = calcFactorial(n - k);
    else
        fatnk = fat[n - k];
    return (double) (fatn/(fatn*fatnk));
}
int Utils::calcFactorial(int n)
{
   if(n==0)
    return 1;
   else return n*calcFactorial(n-1);
}
double Utils::ln(int n){
    return log(n)/log(E);
}
