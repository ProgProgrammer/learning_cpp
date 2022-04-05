#include "RingBuffer.h"

RingBuffer::RingBuffer(unsigned int n) : qsize(n), count(0)
{
    start = end = NULL;
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
        end->next = add;  // ”казатель end - посредник указатель на экземпл€р структуры start.
                          // Ѕез него будет возможно создать только один вложенный экземпл€р структуры.
    end = add;

    if (count < qsize)
    {
        count++;
    }

    return true;
}

void RingBuffer::read()
{
    if (start == NULL)
    {
        std::cout << "exception occurs" << std::endl;
        throw std::runtime_error("start pointer is NULL");
    }
    else
    {
        std::string str = "ch = ";
        str += start->str;

        if (start->next != NULL)
        {
            str += ", buffer: ";
            str += start->next->str;
        }
        else
            str += " buffer: empty";

        Ring_buf* temp = start;
        start = start->next;
        delete temp;

        count--;

        if (count == 0)
        {
            end = NULL;
        }

        std::cout << str << std::endl;
    }
}