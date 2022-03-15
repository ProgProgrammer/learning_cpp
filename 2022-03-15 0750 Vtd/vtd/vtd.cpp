#include "vtd.h"

namespace vtd
{
    void vstring::addStr(const char* s)
    {
        int length = std::strlen(s);
        str = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            str[i] = s[i];
        }

        str[length] = '\0';
    }

    vstring::vstring() { str = new char[1]; strcpy(str, ""); }

    vstring::vstring(const char* s)
    {
        addStr(s);
    }

    vstring::~vstring()
    {
        if (std::strlen(str) > 0)
            delete[] str;
    }

    void vstring::operator=(const char* s)
    {
        addStr(s);
    }

    void operator>>(std::istream& is, vstring& str)
    {
        if (std::strlen(str.str) > 0)
            delete[] str.str;

        str.str = new char[std::strlen(str.str) + 1];

        is.getline(str.str, std::strlen(str.str + 1));
    }

    std::ostream& operator<<(std::ostream& os, const vstring& str)
    {
        os << str.str;

        return os;
    }
}