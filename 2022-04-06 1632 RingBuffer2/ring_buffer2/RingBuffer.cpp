#include "RingBuffer.h"

RingBuffer::RingBuffer(int & num) : char_size(sizeof(char)), count(0)
{
    arr_str = new char[num + 1];
    start = &arr_str[0];
    writeptr = &arr_str[0];
    readptr = &arr_str[0];
    end = &arr_str[num];
}

RingBuffer::~RingBuffer()
{
    if (arr_str != nullptr)
        delete [] arr_str;
}

void RingBuffer::write(const char & ch)
{
    if (writeptr != end)
    {
        *writeptr = ch;
        writeptr = writeptr + char_size;

        if (start + count != end)
            count += char_size;
    }
    else
    {
        writeptr = start;
        *writeptr = ch;
        writeptr = writeptr + char_size;
    }
}

char RingBuffer::read()
{
    char ch;

    if (readptr != (start + count))
    {
        ch = *readptr;
        readptr = readptr + char_size;
    }
    else
    {
        readptr = start;
        ch = *readptr;
    }

    return ch;
}