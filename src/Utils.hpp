#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <math.h>
#include <random>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <string>
#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#include <process.h>
#elif defined(__linux__)
#define PLATFORM_NAME "linux" // Linux
#include <unistd.h>
#else
#define PLATFORM_NAME "unknown"
#endif

#define E 2.71828182845904523536
#define EP 1.0E-5
using namespace std;

class Utils
{
public:
  Utils();
  Utils(unsigned long int seed);
  double getRandomNumber();
  double binomialCoefficient(int qnt, int coef);
  double ln(double n);
  double getCurrentTime();
  double getMinDouble(double *array, int size);
  void saveToCSV(string buffer, string filename);
  void saveToCSVNoOverwriting(string buffer, string filename);
  void saveToTXT(string buffer, string filename);
  string getCurrentDateTime();
  string extractFileName(string name);
  unsigned long int getSeed();

  ~Utils();

private:
  long int calcFactorial(int n);
  void generateFat();
  long int fat[11];
  unsigned long seed;
};
#endif
