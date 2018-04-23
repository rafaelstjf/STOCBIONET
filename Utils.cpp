#include "Utils.hpp"
//used to mix the seed
// http://www.concentric.net/~Ttwang/tech/inthash.htm
unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a = a - b;
    a = a - c;
    a = a ^ (c >> 13);
    b = b - c;
    b = b - a;
    b = b ^ (a << 8);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 13);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 12);
    b = b - c;
    b = b - a;
    b = b ^ (a << 16);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 5);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 3);
    b = b - c;
    b = b - a;
    b = b ^ (a << 10);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 15);
    return c;
}

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
    unsigned long seed = mix(clock(), time(NULL), getpid());
    stringstream s;
    s << seed;
    saveToTXT(s.str(), "last_seed");
    srand(seed);
}
Utils::~Utils()
{
}

double Utils::getRandomNumber()
{
    double i = 0.0;
    while (i == 0.0)
        i = rand() / (float)(RAND_MAX);
    return i;
}
double Utils::binomialCoefficient(int k, int n)
{
    // k!/n!*(k-n)!
    int fatn = 1, fatk = 1;
    if (n > k || (k == 0 && n != 0))
        return 0;
    if (n > 10)
        fatn = calcFactorial(n);
    else
        fatn = fat[n];
    for (int i = k; i < k - n; i--)
    {
        fatk *= i;
    }
    return (double)(fatk / fatn);
}
int Utils::calcFactorial(int n)
{
    if (n == 0)
        return 1;
    else
        return n * calcFactorial(n - 1);
}
double Utils::ln(double n)
{
    return (double)log(n) / log(E);
}
double Utils::log10(double n)
{
    return (double)log(n) / log(10);
}
double Utils::getCurrentTime()
{
    clock_t t;
    t = clock();
    return (double)t / (CLOCKS_PER_SEC);
}
double Utils::getMinDouble(double *array, int size)
{
    double min = 0;
    if (size > 0)
    {
        min = array[0];
        for (int i = 1; i < size; i++)
        {
            if (min > array[i])
                min = array[i];
        }
    }
    return min;
}
void Utils::saveToCSV(string buffer, string filename)
{
    fstream file;
    file.open(filename + ".csv", fstream::out | fstream::trunc);
    if (file.is_open())
    {
        file << buffer;
        file.close();
    }
    else
        cout << "Impossible to save file!" << endl;
}
void Utils::saveToTXT(string buffer, string filename)
{
    fstream file;
    file.open(filename + ".txt", fstream::out | fstream::trunc);
    if (file.is_open())
    {
        file << buffer;
        file.close();
    }
}
