#include "sort.h"
#include <algorithm>  // sort

std::vector<std::vector<int>> Sort::sort(std::vector<int> arr, int parts)
{
    int first = 0;
    int count = arr.size();
    int last = arr.size() / 25;
    int num_part_arr = last;
    std::vector<int> arr_part;
    std::vector<std::vector<int>> arr_result;

    /*for (int i = first; i < count; ++i)
    {
        arr_part.push_back(arr[i]);

        if (i == last - 1)
        {
            std::sort(arr_part.begin(), arr_part.end());  // сортировка
            arr_result.push_back(arr_part);
            arr_part.clear();
            first = last;
            last += num_part_arr;
        }
    }*/

    std::sort(arr.begin(), arr.end());

    return arr_result;
}

std::vector<int> Sort::arrUnion(std::vector<std::vector<int>> arr)
{
    std::vector<int> arr_result;
    return arr_result;
}

std::vector<int> Sort::startLoop(std::vector<int> arr, int parts)
{
    std::vector<std::vector<int>> arr_sort = sort(arr, parts);
    std::vector<int> arr_result = arrUnion(arr_sort);

    return arr_result;
}