#include <iostream>

const double* f1(const double* arr, int n)
{
    double num = n;
    const double* num2 = &num;

    return num2;
}

int main(int argc, char* argv[])
{
    auto p1 = f1;
    const int num = 4;
    const double arr[num] = { 0.1, 1.2, 3, 4 };
    const double* n = (*p1)(arr, 4);
    // std::cout << n << " " << *n << std::endl; // 000000186B0FF668 -9.25596e+61
    std::cout << *n; // 4

    return 0;
}