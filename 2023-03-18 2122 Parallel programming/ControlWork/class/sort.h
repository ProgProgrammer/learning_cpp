#pragma once
#include <vector>
#include <iterator>


class Sort
{
private:
    using It = std::vector<int>::iterator;
    std::vector<int> getRandomVector(int size);
    void printVector(It begin, It end);
    void printVector(std::vector<int>& vec);
    std::vector<std::pair<It, It>> getSliceIterators(std::vector<int>& vec, size_t sliceCount);
    void getArr(std::vector<int> arr_left, std::vector<int> arr_right, std::vector<std::vector<int>>& middle_arr);
    std::vector<int> getArrUnion(std::vector<std::pair<It, It>>& vec);

public:
    void startLoop(std::vector<int>& arr, size_t parts, int size);
};