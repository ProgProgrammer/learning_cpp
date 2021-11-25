#include <iostream>

#define SQUARE(X) X*X // C

inline double square(double x) { return x * x; }     // C++

inline int n_match(double* arr, const int n, double num) // c++
{
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] != num)
        {
            count++;
        }
    }

    return count;
}

int main()
{
    double a = SQUARE(5.0);

    std::cout << a << std::endl;

    a = square(5.0);

    std::cout << a << std::endl;

    double n = 3.3;
    const int num = 10;
    double arr[num] = { 1.5, 2.1, 3.3, 5.05, 3.3, 1, 85, 3.3, 0, 3.3 };

    int count = n_match(arr, num, n);

    std::cout << count << std::endl;

    return 0;
}