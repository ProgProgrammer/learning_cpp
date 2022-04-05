#include "RingBuffer.h"

RingBuffer::RingBuffer(unsigned int n) : qsize(n), count(0)
{
    start = end = nullptr;
}

RingBuffer::~RingBuffer()
{
    Ring_buf * temp;

    while (start != nullptr)
    {
        temp = start;
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
        Ring_buf * temp = start;
        start = start->next;
        delete temp;
    }

    Ring_buf * add = new Ring_buf;

    add->str = ch;
    add->next = nullptr;

    if (start == nullptr)
        start = add;
    else
        end->next = add;  // ”казатель end - посредник указатель на экземпл€р структуры start.
                          // Ѕез него будет возможно создать только один вложенный экземпл€р структуры.
    end = add;

    if (count < qsize)
    {
        count++;
    }
}

Ring_buf RingBuffer::read()
{
    Ring_buf ret;

    if (start == nullptr)
    {
        std::cout << "exception occurs" << std::endl;
        throw std::runtime_error("start pointer is nullptr");
    }
    else
    {
        Ring_buf * temp = start;
        start = start->next;
        ret = *temp;
        delete temp;

        count--;

        if (count == 0)
        {
            end = nullptr;
        }
    }

    return ret;
}