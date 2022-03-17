#pragma once
#include <iostream>
#pragma warning(disable : 4996)

class StringBad
{
private:
    char* str;
    int len;
    static int num_strings;

public:
    StringBad(const char* s);
    StringBad();
    ~StringBad();

    friend std::ostream& operator<<(std::ostream& os, const StringBad& st);
};