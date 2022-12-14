#include <iostream>
#include <array>

const int num = 3;

std::array<int, num> changeArr(std::array<int, num>* arr, const int n)
{
    std::array<int, num> a_arr = *arr;

    for (int i = 0; i < n; i++)
    {
        std::cout << a_arr[i] << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0; i < n; i++)
    {
        a_arr[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << a_arr[i] << std::endl;
    }

    return a_arr;
}

int main()
{
    std::array<int, num> arr = { 1, 2, 3 };

    for (int i = 0; i < num; i++)
    {
        std::cout << arr[i] << std::endl;
    }

    std::cout << std::endl << "Function = " << std::endl;

    std::array<int, num> arr2 = changeArr(&arr, num);

    std::cout << std::endl << "Result = " << std::endl;

    for (int i = 0; i < num; i++)
    {
        std::cout << arr2[i] << std::endl;
    }

    return 0;
}