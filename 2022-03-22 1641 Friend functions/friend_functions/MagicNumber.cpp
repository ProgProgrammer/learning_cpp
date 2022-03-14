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

MagicNumber MagicNumber::operator<<(const int & num) const
{
    std::string str = str_number + std::to_string(num);
    checkNumber(atoi(str.c_str()));
    MagicNumber magic(atoi(str.c_str()));

    return magic;
}

MagicNumber MagicNumber::operator>>(const int & num) const
{
    if (atoi(str_number.c_str()) < 0)
    {
        int str_num = atoi(str_number.c_str());
        str_num = abs(str_num);

        std::string str = "-" + std::to_string(num) + std::to_string(str_num);
        checkNumber(atoi(str.c_str()));
        MagicNumber magic(atoi(str.c_str()));

        return magic;
    }

    std::string str = std::to_string(num) + str_number;
    checkNumber(atoi(str.c_str()));
    MagicNumber magic(atoi(str.c_str()));

    return magic;
}

MagicNumber MagicNumber::operator+(const int & num) const
{
    int i_sum = atoi(str_number.c_str()) + num;
    checkNumber(i_sum);
    MagicNumber sum(i_sum);

    return sum;
}

MagicNumber MagicNumber::operator-(const int & num) const
{
    int i_sub = atoi(str_number.c_str()) - num;
    checkNumber(i_sub);
    MagicNumber sub(i_sub);

    return sub;
}

std::ostream& operator<<(std::ostream& os, const MagicNumber& st)
{
    os << st.str_number;

    return os;
}