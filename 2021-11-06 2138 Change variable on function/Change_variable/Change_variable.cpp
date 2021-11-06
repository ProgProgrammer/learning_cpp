#include <iostream>

void zero_variable(int* var)
{
    *var = 0;
}

int main()
{
    int a = 4;
    std::cout << a << std::endl;
    zero_variable(&a);
    std::cout << a << std::endl;

    return 0;
}