#include "Utils.h"

Utils::Utils()
{
    double seed = clock();
    srand(seed);
    lastSeed.open("Last_Seed.txt", ofstream::out | ofstream::trunc);
    if (lastSeed.is_open())
    {
        lastSeed << "Last seed used: " << seed;
        lastSeed.close();
    }
    else
        cout << "Failed to save the last seed!" << endl;
}
Utils::Utils(double seed)
{
    srand(seed);
    lastSeed.open("Last_Seed.txt", ofstream::out | ofstream::trunc);
    if (lastSeed.is_open())
    {
        lastSeed << "Last seed used: " << seed;
        lastSeed.close();
    }
    else
        cout << "Failed to save the last seed!" << endl;
}
double Utils::getRandomNumber()
{
    return rand() / (float)(RAND_MAX + 1.0);
}
Utils::~Utils()
{
}