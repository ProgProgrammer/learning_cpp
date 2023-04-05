#include "sort.h"
#include "omp.h"
#include <algorithm>
#include <iostream>
#include <thread>
#include <ctime>


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

void Sort::getArr(std::vector<int> arr_left, std::vector<int> arr_right, std::vector<std::vector<int>>& middle_arr)
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

    middle_arr.push_back(arr);
}

std::vector<int> Sort::getArrUnion(std::vector<std::pair<It, It>>& vec)
{
    std::vector<int> result_arr;
    std::vector<int> arr_left;
    std::vector<int> arr_right;
    std::vector<std::vector<int>> middle_arr;
    int arr_size = vec.size();
    int count = 1;

    std::vector<std::thread> arr_threads;  // ������ �������

    for (auto& slice : vec)
    {
        if (count % 2 == 0)
        {
            for (auto it = slice.first; it != slice.second; ++it)
            {
                auto& item = *it;
                arr_right.push_back(item);
            }

            //getArr(arr_left, arr_right, middle_arr);
            arr_threads.push_back(std::thread(&Sort::getArr, Sort(), arr_left, arr_right, std::ref(middle_arr)));
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

        if (arr_size % 2 != 0 && count == arr_size)
        {
            //getArr(arr_left, arr_right, middle_arr);
            arr_threads.push_back(std::thread(&Sort::getArr, Sort(), arr_left, arr_right, std::ref(middle_arr)));
        }

        ++count;
    }

    for (int i = 0; i < arr_threads.size(); i++)
    {
        if (arr_threads[i].joinable())  // ��� �������� ������������� ������
        {
            arr_threads[i].join();  // �������� ���������� ������
        }
    }

    int middle_count = middle_arr.size();
    arr_threads.clear();  // ������� ������� �������
    arr_left.clear();

    while (middle_arr.size() > 1)
    {
        std::vector<std::vector<int>> arr;

        for (int i = 0; i < middle_count; i += 2)
        {
            if (middle_arr.size() % 2 != 0 && i == middle_count - 1)
            {
                arr_threads.push_back(std::thread(&Sort::getArr, Sort(), arr_left, middle_arr[i], std::ref(arr)));
            }
            else
            {
                arr_threads.push_back(std::thread(&Sort::getArr, Sort(), middle_arr[i], middle_arr[i + 1], std::ref(arr)));
            }
        }

        for (int i = 0; i < arr_threads.size(); i++)
        {
            if (arr_threads[i].joinable())  // ��� �������� ������������� ������
            {
                arr_threads[i].join();  // �������� ���������� ������
            }
        }

        arr_threads.clear();
        middle_arr = arr;
        middle_count = middle_arr.size();
    }

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
    size_t threadCount = parts;
    auto sliceIterators = getSliceIterators(vec, threadCount);
    std::cout << "Threads size = " << sliceIterators.size();
    clock_t start = clock();
    std::vector<int> arr_result = getArrUnion(sliceIterators);
    clock_t end = clock();

    std::cout << std::endl << arr_result.size();
    std::cout << std::endl << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s." << std::endl;
}