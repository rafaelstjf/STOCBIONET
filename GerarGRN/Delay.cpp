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
void Delay::setValue(double value)
{
    this.value = value;
}
void Delay::setVariation(double variation)
{
    this.variation = variation;
}
