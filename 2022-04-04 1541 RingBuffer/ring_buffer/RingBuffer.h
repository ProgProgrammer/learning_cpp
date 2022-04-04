#pragma once
#include <iostream>

class RingBuffer
{
    struct Ring_buf
    {
        std::string str;
        Ring_buf * next;
    };

    Ring_buf * start;
    Ring_buf * end;
    const unsigned int qsize;
    unsigned int count;

public:
    RingBuffer(unsigned int n);
    ~RingBuffer();
    bool write(const std::string ch);
    std::string read();
};