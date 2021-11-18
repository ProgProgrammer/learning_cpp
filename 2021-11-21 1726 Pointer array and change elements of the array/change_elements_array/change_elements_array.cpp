#include <iostream>

void changeArray(int* begin, int* end, const int num);

int main()
{
    const int num = 3;
    int arr[num] = { 1, 2, 3 };

    changeArray(&arr[0], &arr[num], num);

    return 0;
}

void changeArray(int* begin, int* end, const int num)
{
    int* arr = begin;

    for (; arr != end; arr++)
    {
        *arr = num;
    }

    std::cout << arr[-3] << " " << arr[-2] << " " << arr[-1] << std::endl;
}