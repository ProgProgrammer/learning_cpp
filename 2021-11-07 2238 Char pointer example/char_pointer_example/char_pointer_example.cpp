#include <iostream>

int main(int argc, char* argv[])
{
    const char* str = "abs";
    str++;
    std::cout << str;
    char b[10];
    char* a = new char[10];
    a = b;
    return 0;
}