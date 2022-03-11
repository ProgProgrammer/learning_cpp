#include "MagicNumber.h"

int main()
{
    MagicNumber number = 100; // или MagicNumber number(100);
    number = number << 1;     // => number = 1001
    number = number << 2;     // => number = 10012
    number = number + 1;      // => number = 10013
    number = number - 1 - 2;  // => number = 10010
    number = number >> 2;     // => number = 210010
    std::cout << number;

    return 0;
}
