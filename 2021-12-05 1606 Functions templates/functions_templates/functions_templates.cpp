#include <iostream>

void may(int n)
{
    std::cout << "1";
}

float may(float n, float n2 = 3)
{
    std::cout << "2";

    return n;
}

void may(char ch)
{
    std::cout << "3";
}

char* may(const char* ch)
{
    std::cout << "4";
    char ch2 = '5';
    char* ch3 = &ch2;

    return ch3;
}

char may(const char& ch)
{
    std::cout << "5";

    return ch;
}

template<typename T>
void may(const  T& n)
{
    std::cout << "6";
}

template<class T>
void may(T* n)
{
    std::cout << "7";
}

int main()
{
    char ch = '6';
    char* ch2 = &ch;
    may(ch2);

    std::cout << std::endl;

    may("Hello");

    return 0;
}
