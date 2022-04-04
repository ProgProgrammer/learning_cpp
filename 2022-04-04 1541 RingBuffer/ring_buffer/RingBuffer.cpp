#include "RingBuffer.h"

RingBuffer::RingBuffer(unsigned int n) : qsize(n), count(0)
{
    start = end = nullptr;
}

RingBuffer::~RingBuffer()
{
    Ring_buf * temp;

    while (start != NULL)
    {
        temp = start;
        start = start->next;
        delete temp;
    }

    if (end != nullptr)
        delete end;
}

bool RingBuffer::write(const std::string ch)
{
    if (count == qsize)
    {
        Ring_buf * temp = start;
        start = start->next;
        delete temp;
    }

    Ring_buf * add = new Ring_buf;

    add->str = ch;
    add->next = NULL;

    if (start == NULL)
        start = add;
    else
        end->next = add;  // Указатель end - посредник указатель на экземпляр структуры start.
                          // Без него будет возможно создать только один вложенный экземпляр структуры.
    end = add;

    if (count < qsize)
    {
        count++;
    }

    return true;
}

std::string RingBuffer::read()
{
    if (start == NULL)
        return "exception occurs";

    std::string r_str = "ch = ";
    r_str += start->str;

    if (start->next != NULL)
    {
        r_str += " buffer: ";
        r_str += start->next->str;
    }
    else
        r_str += " buffer: empty";

    Ring_buf * temp = start;
    start = start->next;
    delete temp;

    count--;

    if (count == 0)
    {
        end = NULL;
    }

    return r_str;
}