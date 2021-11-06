#include <iostream>

void zero_variable_by_pointer(int* var)
{
    *var = 0;
}

void zero_variable_by_reference(int & var)
{
    var = 1;
}

int main()
{
    int a = 4;
    std::cout << a << std::endl;
    zero_variable_by_pointer(&a);
    std::cout << a << std::endl;
    zero_variable_by_reference(a);
    std::cout << a << std::endl;

    return 0;
}