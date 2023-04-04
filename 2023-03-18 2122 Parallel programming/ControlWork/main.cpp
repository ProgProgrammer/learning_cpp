#include "class/sort.h"
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

using It = std::vector<int>::iterator;

std::vector<int> getRandomVector(int size)
{
    srand(time(0));

    std::vector<int> result(size, 0);
    std::generate(result.begin(), result.end(), rand);
    return result;
}

void printVector(It begin, It end)
{
    for (auto it = begin; it != end; ++it)
    {
        auto& item = *it;
        std::cout << item << " ";
    }
}

void printVector(std::vector<int>& vec)
{
    printVector(vec.begin(), vec.end());
}


std::vector<std::pair<It, It>> getSliceIterators(std::vector<int>& vec, size_t sliceCount)
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

std::vector<int> getArrUnion(std::vector<std::pair<It, It>>& vec)
{
    std::vector<int> result_arr;

    for (auto& slice : vec)
    {
        for (auto it = slice.first; it != slice.second; ++it)
        {
            auto& item = *it;
            result_arr.push_back(item);
        }
    }

    std::sort(result_arr.begin(), result_arr.end());

    return result_arr;
}

int main()
{
    std::vector<int> arr;
    int parts = 4;
    int size = 21;
    Sort sort;
    sort.startLoop(arr, parts, size);
    /*auto vec = getRandomVector(20);
    std::cout << "Before:\n";
    printVector(vec);

    // option 1
    // std::sort(vec.begin(), vec.end());

    // option 2
    size_t threadCount = 4;
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

    std::vector<int> arr = getArrUnion(sliceIterators);
    printVector(arr);

    std::cout << std::endl;*/
}

/*#include <iostream>
#include "class\sort.h"

int main()
{
    Sort sort;
    std::vector<int> arr;
    int parts = 25;

    for (int i = 0; i < 30000; ++i)
    {
        arr.push_back(rand());
    }

    sort.startLoop(arr, parts);
    std::cout << arr[0] << " " << arr[arr.size() - 1];
}*/