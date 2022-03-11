#pragma once
#include <iostream>
#include <climits>
#include <string>

class MagicNumber
{
private:
    std::string str_number = "";

public:
    MagicNumber(int num);

    MagicNumber operator<<(const int & num) const;
    MagicNumber operator>>(const int & num) const;
    MagicNumber operator+(const int & num) const;
    MagicNumber operator-(const int& num) const;
    friend std::ostream & operator<<(std::ostream & os, const MagicNumber & st);
};