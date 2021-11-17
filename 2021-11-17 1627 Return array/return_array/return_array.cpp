#include <iostream>
#include <array>

std::array* changeArr(int* arr, const int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << std::endl;
    }

    return arr;
}

int main()
{
    const int num = 3;
    std::array<int, num> arr = { 1, 2, 3 };

    for (int i = 0; i < num; i++)
    {
        std::cout << arr[i] << std::endl;
    }

    std::cout << std::endl << "Function = " << std::endl;

    std::array<int, num> * arr2 = changeArr(arr, num);

    std::cout << std::endl << "Result = " << std::endl;

    for (int i = 0; i < num; i++)
    {
        std::cout << arr2[i] << std::endl;
    }

    return 0;
}