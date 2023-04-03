#include <iostream>
#include "class\sort.h"

int main()
{
    Sort sort;
    std::vector<int> arr;
    int parts = 25;

    for (int i = 0; i < 131072000; ++i)
    {
        arr.push_back(rand());
    }

    std::vector<int> arr_result = sort.startLoop(arr, parts);
}