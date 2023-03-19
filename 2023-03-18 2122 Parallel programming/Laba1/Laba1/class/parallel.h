#pragma once
#include <time.h>

class Parallel
{
private:
    clock_t start;
    clock_t end;
    double elapsedTime(clock_t start, clock_t end)
    {
        return (double)(end - start) / CLOCKS_PER_SEC;
    }

public:
    void one_task();
    void two_task();
    void three_task();
};