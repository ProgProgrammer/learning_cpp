#include "sort.h"

std::vector<int> Sort::hoarasort(std::vector<int> arr, int first, int last)
{
    int i = first, j = last;
    double tmp, x = arr[(first + last) / 2];

    do {
        while (arr[i] < x)
            i++;
        while (arr[j] > x)
            j--;

        if (i <= j)
        {
            if (i < j)
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        hoarasort(arr, i, last);
    if (first < j)
        hoarasort(arr, first, j);
    if (i == last)
    {
        return arr;
    }
}

std::vector<std::vector<int>> Sort::sort(std::vector<int> arr, int parts)
{
    int first = 0;
    int last = arr.size() / 25;
    std::vector<std::vector<int>> arr_result;
    arr_result.push_back(hoarasort(arr, first, last));

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