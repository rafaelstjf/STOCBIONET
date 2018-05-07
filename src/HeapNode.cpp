#include "../include/HeapNode.hpp"

HeapNode::HeapNode(){
    index = 0;
    time = 0.0;
}
HeapNode::HeapNode(int index, double time){
    this->index = index;
    this->time = time;
}
HeapNode::~HeapNode(){

}

void HeapNode::setIndex(int index){
    this->index = index;
}
void HeapNode::setTime(double time){
    this->time = time;
}
int HeapNode::getIndex(){
    return index;
}
double HeapNode::getTime(){
    return time;
}