#include "DelayNode.hpp"

DelayNode::DelayNode(int specIndex, int reacIndex, double delayTime)
{
    this->specIndex = specIndex;
    this->reacIndex = reacIndex;
    this->delayTime = delayTime;
}
DelayNode::~DelayNode()
{
}
void DelayNode::setDelayTime(double delayTime)
{
    this->delayTime = delayTime;
}
void DelayNode::setSpecIndex(int specIndex)
{
    this->specIndex = specIndex;
}
void DelayNode::setReacIndex(int reacIndex)
{
    this->reacIndex = reacIndex;
}
double DelayNode::getDelayTime()
{
    return delayTime;
}
int DelayNode::getReacIndex()
{
    return reacIndex;
}
int DelayNode::getSpecIndex()
{
    return specIndex;
}