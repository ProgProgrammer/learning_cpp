#include "iostream"
#include <vector>
#include <time.h>
#include "classes/sorts.h"

double elapsedTime(clock_t start, clock_t end)
{
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main()
{
    const int min_count = 10000;
    const int mid_count = 30000;
    const int max_count = 60000;

    std::vector<int> arr_min;
    std::vector<int> arr_mid;
    std::vector<int> arr_max;

    for (int i = 0; i < min_count; ++i)
    {
        arr_min.push_back(i);
    }

    for (int i = 0; i < mid_count; ++i)
    {
        arr_mid.push_back(i);
    }

    for (int i = 0; i < max_count; ++i)
    {
        arr_max.push_back(i);
    }

    clock_t start;
    clock_t end;

    sorts::RadixSort radix_object;
    start = clock();
    radix_object.startLoop(arr_min, min_count);
    end = clock();
    std::cout << "Radix minimum sorting completed in " << elapsedTime(start, end) << " seconds." << std::endl;

    start = clock();
    radix_object.startLoop(arr_mid, mid_count);
    end = clock();
    std::cout << "Radix middle sorting completed in " << elapsedTime(start, end) << " seconds." << std::endl;

    start = clock();
    radix_object.startLoop(arr_max, max_count);
    end = clock();
    std::cout << "Radix maximum sorting completed in " << elapsedTime(start, end) << " seconds." << std::endl;

    sorts::SelectionSort selection_sort;
    start = clock();
    selection_sort.startLoop(arr_min, min_count);
    end = clock();
    std::cout << std::endl << "Selection minimum sorting completed in " << elapsedTime(start, end) << " seconds." << std::endl;

    start = clock();
    selection_sort.startLoop(arr_mid, mid_count);
    end = clock();
    std::cout << "Selection middle sorting completed in " << elapsedTime(start, end) << " seconds." << std::endl;

    start = clock();
    selection_sort.startLoop(arr_max, max_count);
    end = clock();
    std::cout << "Selection maximum sorting completed in " << elapsedTime(start, end) << " seconds." << std::endl;

    sorts::HeapSort heap_sort;
    start = clock();
    heap_sort.startLoop(arr_min, min_count);
    end = clock();
    std::cout << std::endl << "Heap minimum sorting completed in " << elapsedTime(start, end) << " seconds." << std::endl;

    start = clock();
    heap_sort.startLoop(arr_mid, mid_count);
    end = clock();
    std::cout << "Heap middle sorting completed in " << elapsedTime(start, end) << " seconds." << std::endl;

    start = clock();
    heap_sort.startLoop(arr_max, max_count);
    end = clock();
    std::cout << "Heap maximum sorting completed in " << elapsedTime(start, end) << " seconds." << std::endl;
}