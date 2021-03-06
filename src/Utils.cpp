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
    generateFat();
    seed = mix(clock(), time(NULL), getpid());
    //unsigned long seed = 1940740546;
}
void Utils::generateFat()
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
Utils::Utils(unsigned long int seed)
{
    generateFat();
    this->seed = seed;
}
Utils::~Utils()
{
}
unsigned long int Utils::getSeed()
{
    return seed;
}
double Utils::getRandomNumber()
{
    //using static to save the same object
    double i = 0.0;
    static mt19937 generator(seed);
    static uniform_real_distribution<double> dist(0.0, 1.0);
    while (i <= EP || i >= 1 - EP)
        i = dist(generator);
    return i;
}
string Utils::getCurrentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%H-%M-%S", &tstruct);

    return buf;
}

double Utils::binomialCoefficient(double qnt, int coef)
{
    //qnt = quantity
    //coef = stoichiometric coefficient
    // qnt!/coef!*(qnt-coef)!
    long int fatn = 1, fatk = 1;
    if (coef > qnt || (qnt == 0 && coef != 0))
        return 0;
    if (coef == 0)
        return 1;
    if (coef > 10)
        fatn = calcFactorial(coef);
    else
        fatn = fat[coef];
    //(qnt*(qnt-1)*...*(qnt-coef)!)/(coef!*(qnt-coef)!)
    //qnt*(qnt-1)*...*(qnt-coef-1)/coef!
    for (int i = qnt; i >= qnt - (coef - 1); i--)
    {
        if (qnt > 0)
            fatk *= i;
    }
    double result = (1.0 * fatk) / fatn;
    return result;
}
long int Utils::calcFactorial(int n)
{
    if (n == 0)
        return 1;
    else
        return n * calcFactorial(n - 1);
}
string Utils::removeFilePath(string name)
{

    int index = (name.size() - 1);
    while (index >= 0)
    {
        if (name[index] == '/')
            break;
        index--;
    }
    return name.substr(index + 1, name.size() - 1);
}
string Utils::removeFileType(string name)
{
    int index = name.size() - 1;
    while (index >= 0)
    {
        if (name[index] == '.')
        {
            break;
        }
        index--;
    }
    return name.substr(0, index);
}
bool Utils::checkIfFileExistsAUX(string name)
{
    /**
 * Check if a file exists
 * @return true if and only if the file exists, false else
 */
    struct stat buf;
    if (stat(name.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}
string Utils::checkIfFileExists(string filename, string fileType)
{
    int index = 0;
    string name = (filename + fileType);
    while (checkIfFileExistsAUX(name) == true)
    {
        index++;
        name = filename + '-' + to_string(index) + fileType;
    }

    cout << "NOME DO ARQUIVO: " << (filename + '-' + to_string(index) + fileType) << endl;
    return (filename + '-' + to_string(index) + fileType);
}
double Utils::ln(double n)
{
    return (double)log(n) / log(E);
}
/*double Utils::log10(double n)
{
    return (double)log(n) / log(10);
}*/
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
void Utils::saveToCSVNoOverwriting(string buffer, string filename)
{
    fstream file;
    fstream existFile;
    int i = 0;
    existFile.open(filename + ".csv", fstream::in);
    while (existFile.good())
    {
        i++;
        existFile.close();
        existFile.open(filename + "_" + to_string(i) + ".csv", fstream::in);
    }
    if (i > 0)
        file.open(filename + "_" + to_string(i) + ".csv", fstream::out);
    else
        file.open(filename + ".csv", fstream::out);
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
