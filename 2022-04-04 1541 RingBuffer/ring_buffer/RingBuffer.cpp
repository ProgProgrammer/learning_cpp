#include "RingBuffer.h"

RingBuffer::RingBuffer(unsigned int n) : qsize(n), count(0)
{
    start = nullptr;
    end = nullptr;
}

RingBuffer::~RingBuffer()
{
    while (start != nullptr)
    {
        RingNode* temp = start;
        start = start->next;
        delete temp;
    }

    if (end != nullptr)
        delete end;
}

void RingBuffer::write(const std::string ch)
{
    if (count == qsize)
    {
        RingNode * temp = start;
        start = start->next;
        delete temp;
    }

    RingNode * add = new RingNode;
    add->str = ch;
    add->next = nullptr;

    if (start == nullptr)
        start = add;     // adding first element
    else
        end->next = add; // if the first element is already present the new one should be added as second

    end = add;

    if (count < qsize)
    {
        count++;
    }
}

std::string RingBuffer::read()
{
    if (start == nullptr)
    {
        throw std::runtime_error("start pointer is nullptr");
    }

    RingNode * temp = start;
    start = start->next;
    std::string ret = temp->str;
    delete temp;

    count--;

    if (count == 0)
    {
        end = nullptr;
    }

    return ret;
}