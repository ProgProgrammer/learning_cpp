#include <iostream>

int& pointer2(int& n)
{
    int x = n;

    return x;
}

int main()
{
    int num1 = 5;
    int& num2 = pointer2(num1);

    std::cout << num2 << std::endl;

    return 0;
}
