#include "Delay.h"

Delay::Delay()
{
    value = 0.0;
    variation = 0.0;
}
Delay::~Delay()
{
}
double Delay::getValue()
{
    return value;
}
double Delay::getVariation()
{
    return variation;
}
void Delay::setValue(double val)
{
    value = val;
}
void Delay::setVariation(double var)
{
    variation = var;
}
