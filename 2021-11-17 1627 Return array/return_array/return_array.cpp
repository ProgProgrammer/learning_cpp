#include <iostream>
#include <array>

std::array* changeArr(int* arr, const int n) // правильный тип возврата, наверное, std::array<int, 3> *, либо нужно писать шаблон
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

    std::array<int, num> * arr2 = changeArr(arr, num);  // std::array<int, num> * - это название полного типа (который возвращается), такой же должен быть в 4 строке
                                                        // num = 3 разворачивается при компиляции, так что правильный тип будет такой: std::array<int, 3> *
                                                        // ты не правильно передаешь первый аргумент. Ты передаешь туда std::array<int, num>, а там ожидается int *

    std::cout << std::endl << "Result = " << std::endl;

    for (int i = 0; i < num; i++)
    {
        std::cout << arr2[i] << std::endl;
    }

    return 0;
}
