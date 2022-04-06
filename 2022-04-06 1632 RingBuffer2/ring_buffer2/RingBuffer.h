#pragma once
#include <iostream>

class RingBuffer
{
    char * start;
    char * end;
    char * writeptr;
    char * readptr;
    int count;
    const int char_size;

public:
    RingBuffer(int & num);
    ~RingBuffer();
    void write(const char & ch);
    char read();
};