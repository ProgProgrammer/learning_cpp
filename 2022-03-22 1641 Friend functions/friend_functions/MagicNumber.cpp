#include "MagicNumber.h"

MagicNumber::MagicNumber(int num)
{
    str_number = std::to_string(num);
}

MagicNumber MagicNumber::operator<<(const int& num) const
{
    std::string str = str_number + std::to_string(num);
    MagicNumber magic(atoi(str.c_str()));

    return magic;
}

MagicNumber MagicNumber::operator>>(const int& num) const
{
    std::string str = std::to_string(num) + str_number;
    MagicNumber magic(atoi(str.c_str()));

    return magic;
}

MagicNumber MagicNumber::operator+(const int & num) const
{
    int i_sum = atoi(str_number.c_str()) + num;
    MagicNumber sum(i_sum);

    return sum;
}

MagicNumber MagicNumber::operator-(const int& num) const
{
    int i_sub = atoi(str_number.c_str()) - num;
    MagicNumber sum(i_sub);

    return sum;
}

std::ostream& operator<<(std::ostream& os, const MagicNumber& st)
{
    os << st.str_number << std::endl;

    return os;
}