#include "RingBuffer.h"

RingBuffer::RingBuffer(int & num) : char_size(sizeof(char)), count(0)
{
    start = new char[num + 1];
    writeptr = &start[0];
    readptr = &start[0];
    end = &start[num];
}

RingBuffer::~RingBuffer()
{
    if (start != nullptr)
        delete [] start;
}

void RingBuffer::write(const char & ch)
{
    if (writeptr < end)
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
        readptr = start;
    }
}

char RingBuffer::read()
{
    char ch;

    if (readptr < (start + count))
    {
        ch = *readptr;
        readptr = readptr + char_size;
    }
    else
    {
        readptr = start;
        ch = *readptr;
        readptr = readptr + char_size;
    }

    return ch;
}