#include "MagicNumber.h"

void MagicNumber::checkNumber(int num) const
{
    if (num < min_num)
    {
        throw std::overflow_error("too small");
    }
    else if (num > max_num)
    {
        throw std::overflow_error("too big");
    }
}

MagicNumber::MagicNumber(int num)
{
    checkNumber(num);
    str_number = std::to_string(num);
}

MagicNumber MagicNumber::operator<<(const int& num) const
{
    std::string str = str_number + std::to_string(num);
    checkNumber(atoi(str.c_str()));
    MagicNumber magic(atoi(str.c_str()));

    return magic;
}

MagicNumber MagicNumber::operator>>(const int& num) const
{
    std::string str = std::to_string(num) + str_number;
    checkNumber(atoi(str.c_str()));
    MagicNumber magic(atoi(str.c_str()));

    return magic;
}

MagicNumber MagicNumber::operator+(const int & num) const
{
    int i_sum = atoi(str_number.c_str()) + num;
    std::cout << i_sum << std::endl;
    checkNumber(i_sum);
    MagicNumber sum(i_sum);

    return sum;
}

MagicNumber MagicNumber::operator-(const int& num) const
{
    int i_sub = atoi(str_number.c_str()) - num;
    checkNumber(i_sub);
    MagicNumber sum(i_sub);

    return sum;
}

std::ostream& operator<<(std::ostream& os, const MagicNumber& st)
{
    os << st.str_number;

    return os;
}