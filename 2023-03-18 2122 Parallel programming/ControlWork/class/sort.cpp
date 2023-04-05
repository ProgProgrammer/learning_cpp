#include "sort.h"
#include <algorithm>
#include <iostream>
#include <thread>


using It = std::vector<int>::iterator;

std::vector<int> Sort::getRandomVector(int size)
{
    srand(time(0));

    std::vector<int> result(size, 0);
    std::generate(result.begin(), result.end(), rand);
    return result;
}

void Sort::printVector(It begin, It end)
{
    for (auto it = begin; it != end; ++it)
    {
        auto& item = *it;
        std::cout << item << " ";
    }
}

void Sort::printVector(std::vector<int>& vec)
{
    printVector(vec.begin(), vec.end());
}

std::vector<std::pair<It, It>> Sort::getSliceIterators(std::vector<int>& vec, size_t sliceCount)
{
    size_t partSize = vec.size() / sliceCount;
    std::vector<std::pair<It, It>> bounds; // pairs of {begin, end}

    auto it = vec.begin();
    for (size_t i = 1; i < sliceCount; ++i)
    {
        auto nextIt = it + partSize;
        auto currentBound = std::make_pair(it, nextIt);
        bounds.push_back(currentBound);

        it = nextIt;
    }
    auto lastBound = std::make_pair(it, vec.end());
    bounds.push_back(lastBound);

    return bounds;
}

std::vector<int> Sort::getArr(std::vector<int> arr_left, std::vector<int> arr_right)
{
    std::vector<int> arr;

    for (int i = 0; i < arr_left.size(); ++i)
    {
        arr.push_back(arr_left[i]);
    }

    for (int i = 0; i < arr_right.size(); ++i)
    {
        arr.push_back(arr_right[i]);
    }

    std::sort(arr.begin(), arr.end());

    return arr;
}

std::vector<int> Sort::getArrUnion(std::vector<std::pair<It, It>>& vec, size_t parts, int size)
{
    std::vector<int> result_arr;
    std::vector<int> arr_left;
    std::vector<int> arr_right;
    std::vector<std::vector<int>> middle_arr;
    int arr_size = vec.size();
    int count = 1;

    for (auto& slice : vec)
    {
        if (count % 2 == 0)
        {
            for (auto it = slice.first; it != slice.second; ++it)
            {
                auto& item = *it;
                arr_right.push_back(item);
            }

            middle_arr.push_back(getArr(arr_left, arr_right));
            arr_left.clear();
            arr_right.clear();
        }
        else
        {
            for (auto it = slice.first; it != slice.second; ++it)
            {
                auto& item = *it;
                arr_left.push_back(item);
            }
        }

        if (arr_size == count && size % 2 != 0)
        {
            std::vector<int> arr;
            middle_arr.push_back(getArr(arr, arr_right));
            break;
        }

        ++count;
    }

    std::sort(middle_arr.begin(), middle_arr.end());

    for (int i = 0; i < middle_arr.size(); ++i)
    {
        for (int a = 0; a < middle_arr[i].size(); ++a)
        {
            result_arr.push_back(middle_arr[i][a]);
        }
    }

    return result_arr;
}

void Sort::startLoop(std::vector<int>& arr, size_t parts, int size)
{
    auto vec = getRandomVector(size);
    std::cout << "Before:\n";
    printVector(vec);
    size_t threadCount = parts;
    auto sliceIterators = getSliceIterators(vec, threadCount);
    std::cout << "\n\nBounds size = " << sliceIterators.size();

    for (auto& slice : sliceIterators)
    {
        std::cout << "\n\n Bound:\n";
        std::sort(slice.first, slice.second);
        printVector(slice.first, slice.second);
    }

    std::cout << "\n\nAfter:\n";
    printVector(vec);
    std::cout << std::endl;
    std::sort(sliceIterators.begin(), sliceIterators.end());
    std::cout << "\n\nResult:\n";

    std::vector<int> arr_result = getArrUnion(sliceIterators, parts, size);
    printVector(arr_result);

    std::cout << std::endl;
}