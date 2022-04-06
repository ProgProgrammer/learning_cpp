#pragma once
#include <iostream>

class RingBuffer
{
    char * start;
    char * end;
    char * writeptr;
    char * readptr;
    unsigned int count;
    const unsigned  int char_size;

public:
    RingBuffer(unsigned int & num);
    ~RingBuffer();
    void write(const char & ch);
    std::string read();
};