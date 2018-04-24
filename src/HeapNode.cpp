#include "../HeapNode.hpp"

HeapNode::HeapNode()
{
}
HeapNode ~HeapNode()
{
}
int HeapNode::getIndex()
{
    return index;
}
double HeapNode::getTime()
{
    return time;
}
void HeapNode::setIndex(int index)
{
    this->index = index;
}
void HeapNode::setTime(double time)
{
    this->time = time;
}