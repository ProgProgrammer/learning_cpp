#pragma once
#include <iostream>

struct Ring_buf
{
    std::string str;
    Ring_buf* next;
};

class RingBuffer
{
    Ring_buf * start;
    Ring_buf * end;
    const unsigned int qsize;
    unsigned int count;

public:
    RingBuffer(unsigned int n);
    ~RingBuffer();
    void write(const std::string ch);
    Ring_buf read();
};