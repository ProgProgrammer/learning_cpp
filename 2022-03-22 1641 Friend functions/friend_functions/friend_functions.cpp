#include "MagicNumber.h"

int main()
{
    try
    {
        MagicNumber number = 100; // или MagicNumber number(100);
        number = number << 1;     // => number = 1001
        number = number << 2;     // => number = 10012
        number = number + 1;      // => number = 10013
        number = number - 20000;  // => number = -9987
        number = number >> 2;     // => number = -29987
        std::cout << number;      // => consolse print: -29987
    }
    catch (const std::overflow_error& exception)
    {
        std::cout << "Error: " << exception.what();
    }

    return 0;
}
