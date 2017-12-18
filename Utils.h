#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <random>
#include <fstream>
#include <time.h>

using namespace std;

class Utils
{
  public:
  Utils();
  Utils(double seed);
  double getRandomNumber();
  ~Utils();
  private:
  ofstream lastSeed;
};
#endif