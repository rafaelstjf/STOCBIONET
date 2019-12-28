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
#include <sys/stat.h>
#if defined(_WIN32)
#define PLATFORM_NAME 0 // Windows
#include <process.h>
#elif defined(__linux__)
#define PLATFORM_NAME 1 // Linux
#include <unistd.h>
#else
#define PLATFORM_NAME 1
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
  double binomialCoefficient(double qnt, int coef);
  double ln(double n);
  double getCurrentTime();
  double getMinDouble(double *array, int size);
  void saveToCSV(string buffer, string filename);
  void saveToCSVNoOverwriting(string buffer, string filename);
  void saveToTXT(string buffer, string filename);
  string getCurrentDateTime();
  string removeFilePath(string name);
  string removeFileType(string name);
  string checkIfFileExists(string filename, string fileType);
  unsigned long int getSeed();

  ~Utils();

private:
  long int calcFactorial(int n);
  bool checkIfFileExistsAUX(string filename);
  void generateFat();
  long int fat[11];
  unsigned long seed;
};
#endif
