#include <iostream>

template <class T1, class T2>
T1 maxn(const T1* arr, const T2 n)
{
    T1 maxNum = arr[0];

    for (int i = 0; i < n; i++)
    {
        if (i > 0 && maxNum < arr[i])
        {
            maxNum = arr[i];
        }
    }

    return maxNum;
}

template <class T>
const char* maxn(const char* arr[], const T n)
{
    unsigned int maxSize = strlen(arr[0]);

    for (int i = 0; i < n; i++)
    {
        if (i > 0 && maxSize < strlen(arr[i]))
        {
            maxSize = strlen(arr[i]);
        }
    }

    std::cout << maxSize << std::endl;
    std::cout << arr[maxSize] << std::endl;

    return arr[maxSize];
}

int main()
{
    int arr_i[6] = { 1, 2, 3, 4, 5, 6 };

    std::cout << maxn(arr_i, 6) << std::endl;

    double arr_d[4] = { 1.1, 2.2, 3.3, 4.4 };

    std::cout << maxn(arr_d, 4) << std::endl;

    const char* str_arr[] = {
                    "Read Error\n",
                    "Write Error\n",
                    "Cannot Open File\n",
                    "Media Failure\n"
    };

    std::cout << maxn(str_arr, 4) << std::endl;

    return 0;
}
