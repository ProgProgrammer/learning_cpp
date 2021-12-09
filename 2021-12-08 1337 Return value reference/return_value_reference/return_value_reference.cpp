#include <iostream>

double& ft(double& n)
{
    double num = n;

    return n;
}

int main()
{
    double num = 25.5;

    std::cout << ft(num) << std::endl;

    std::cout << typeid(ft(num)).name() << " " << ft(num) << std::endl;

    return 0;
}