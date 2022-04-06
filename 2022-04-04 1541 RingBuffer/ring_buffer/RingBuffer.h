#pragma once
#include <iostream>

struct RingNode
{
    std::string str;
    RingNode* next;
};

class RingBuffer
{
    RingNode * start;
    RingNode * end;
    const unsigned int qsize;
    unsigned int count;

public:
    RingBuffer(unsigned int n);
    ~RingBuffer();
    void write(const std::string ch);
    std::string read();
};