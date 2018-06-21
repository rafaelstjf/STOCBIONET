#include "../include/log/Node.hpp"

Node::Node()
{
}
Node::~Node()
{
    dict.clear();
}

void Node::setNext(Node *next)
{
    this->next = next;
}
void Node::setPrevious(Node *previous)
{
    this->previous = previous;
}
void Node::setTime(double time)
{
    this->time = time;
}
Node *Node::getNext()
{
    return next;
}
Node *Node::getPrevious()
{
    return previous;
}
double Node::getTime()
{
    return time;
}
map<int, int> Node::getDict()
{
    return dict;
}
int Node::getValIndex(int index)
{
    map<int, int>::iterator it = dict.find(index);
    if (it == dict.end())
        return -1 * INT_MAX;
    else
        return it->second;
}
bool Node::checkExists(int index)
{
    if(dict.find(index) != dict.end())
        return true;
    else
        return false;
}
int Node::getValIndexFather(int index)
{
    Node* it = previous;
    if(checkExists(index))
        return getValIndex(index);
    else
    {
        while(it!= nullptr && !it->checkExists(index))
        {
            it = it->getPrevious();
        }
        if(it!= nullptr)
            return it->getValIndex(index);
    }
}
void Node::insertSpecie(int index, int value, int* array)
{
    Node *it = previous;
    if(previous==nullptr)
    {
        dict.insert(pair<int, int>(index, value));
        array[index] = value;
    }
    else
    {
        if(array[index] != value)
        {
            while (it != nullptr && !it->checkExists(index))
            {
                it = it->getPrevious();
            }
            if (it != nullptr)
            {
                //found index on a previous node
                if (it->getValIndex(index) != value)
                {
                    dict.insert(pair<int, int>(index, value));
                    array[index] = value;
                }

            }
        }

    }
}
