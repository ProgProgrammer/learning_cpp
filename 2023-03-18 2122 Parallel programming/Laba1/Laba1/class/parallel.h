#pragma once
#include <time.h>
#include <iostream>

class Parallel
{
private:
    double elapsedTime(clock_t start, clock_t end)
    {
        return (double)(end - start) / CLOCKS_PER_SEC;
    }
    void one_task();
    void two_task();
    void three_task();
    void four_task();
    void five_task();

public:
    void startLoop()
    {
        std::cout << "One Task:" << std::endl;
        one_task();
        std::cout << std::endl << std::endl << "Two Task:" << std::endl;
        two_task();
        std::cout << std::endl << "Three Task:" << std::endl;
        three_task();
        std::cout << std::endl << "Four Task:" << std::endl;
        four_task();
    }
};