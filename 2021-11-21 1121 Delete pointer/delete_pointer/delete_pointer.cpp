#include <iostream>

std::string* buildstr() // функция, возращающая указатель
{
    std::string* pstr = new std::string; // указатель на кучу, который будет возвращен

    *pstr = "Hello, world!";

    return pstr; // возврат указателя
}

int main()
{
    std::string* ps = buildstr(); // создание указателя на функцию и присвоение ему возвращаемого функцией указателя

    std::cout << *ps << std::endl;

    delete[] ps; // освобождение памяти

    return 0;
}