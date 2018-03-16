#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <math.h>
#include <random>
#define E 2.71828182845904523536
using namespace std;



class Utils
{
  public:
  Utils();
  double getRandomNumber();
  double binomialCoefficient(int k, int n);
  double ln(double n);
  ~Utils();
  private:
  int calcFactorial(int n);
  int fat[11];
  random_device rd; //obtain a seed
};
#endif
