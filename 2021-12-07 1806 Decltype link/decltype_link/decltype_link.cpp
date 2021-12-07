#include <iostream>

int main()
{
    double xx = 4.4;
    decltype ((xx)) r2 = xx;

    std::cout << typeid(r2).name() << std::endl;

    return 0;
}
