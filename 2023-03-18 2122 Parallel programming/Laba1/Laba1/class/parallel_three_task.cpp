#include "parallel.h"
#include <vector>
#include <omp.h>

void Parallel::three_task()
{
    std::vector<int> arr = { 1, 2, 3, 4, 5, 6 };
    std::vector<std::vector<int>> arr_left;
    std::vector<std::vector<int>> arr_right;
    const int count = 6;
    int i;
    int j;

    for (int i = 0; i < count; ++i)
    {
        arr_left.push_back(arr);
        arr_right.push_back(arr);
    }

    clock_t start;
    clock_t end;
    start = clock();
#pragma omp parallel default (shared) private (i, j)
#pragma omp for ordered
    for (i = 0; i < count; ++i)
    {
        for (j = 0; j < count; ++j)
        {
            arr[i] += arr_left[i][j] * arr_right[i][j];
        }

        if (i < count)
        {
            printf("Z(% d) = % d\n", i, arr[i]);
        }
    }
    end = clock();
    std::cout << "Time = " << elapsedTime(start, end) << std::endl;
}