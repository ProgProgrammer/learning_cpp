#pragma once
#include <vector>

class Sort
{
private:
    std::vector<std::vector<int>> sort(std::vector<int> arr, int parts);
    std::vector<int> arrUnion(std::vector<std::vector<int>> arr);

public:
    std::vector<int> startLoop(std::vector<int> arr, int parts);
};