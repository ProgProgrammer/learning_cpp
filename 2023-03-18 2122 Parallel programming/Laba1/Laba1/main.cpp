#include "class\parallel.h"
#include <iostream>

int main()
{
    Parallel obj;
    std::cout << "One Task:" << std::endl;
    obj.one_task();
    std::cout << std::endl << std::endl << "Two Task:" << std::endl;
    obj.two_task();
    std::cout << std::endl << "Three Task:" << std::endl;
    obj.three_task();
}