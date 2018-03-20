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
     double seed = rd();
     srand(seed);

}
Utils::~Utils()
{
}

double Utils::getRandomNumber()
{
    return rand() / (float)RAND_MAX;
}
double Utils::binomialCoefficient(int k, int n)
{
    // k!/n!*(k-n)!
    int fatn, fatk=1, fatkn;
    /* it's not necessary to calculate all the fatorials
    if(k <=0 || n <= 0)
        return 0;
    if (n > 10)
        fatn = calcFactorial(n);
    else
        fatn = fat[n];
    if (k > 10)
        fatk = calcFactorial(k);
    else
        fatk = fat[k];
    if (k - n > 10)
        fatkn = calcFactorial(k - n);
    else
        fatkn = fat[k - n];
    return (double) (fatk/(fatn*fatkn));
    */
    if(k <=0 || n <= 0 || n > k)
        return 0;
    if (n > 10)
        fatn = calcFactorial(n);
    else
        fatn = fat[n];
    for(int i = k; i < k-n;i--){
        fatk*=i;
    }
    return (double) (fatk/fatn);
}
int Utils::calcFactorial(int n)
{
   if(n==0)
    return 1;
   else return n*calcFactorial(n-1);
}
double Utils::ln(double n){
    return (double)log(n)/log(E);
}
double Utils::getCurrentTime(){
    clock_t t;
    t = clock();
    return (double)t/(CLOCKS_PER_SEC);
}
void Utils::saveToCSV(string buffer){
    fstream file;
    file.open("output.csv", fstream::out | fstream::trunc);
    if(file.is_open()){
        file << buffer;
        file.close();
    }
    else
        cout << "Impossible to save file!" << endl;
}
