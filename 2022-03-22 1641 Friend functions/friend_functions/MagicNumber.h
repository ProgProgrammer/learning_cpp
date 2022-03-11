#pragma once
#include <iostream>
#include <climits>
#include <string>

class MagicNumber
{
private:
    std::string str_number = "";
    int min_num = SHRT_MIN;
    int max_num = SHRT_MAX;
    void checkNumber(int num) const;

public:
    MagicNumber(int num);

    MagicNumber operator<<(const int & num) const;
    MagicNumber operator>>(const int & num) const;
    MagicNumber operator+(const int & num) const;
    MagicNumber operator-(const int& num) const;
    friend std::ostream & operator<<(std::ostream & os, const MagicNumber & st);
};