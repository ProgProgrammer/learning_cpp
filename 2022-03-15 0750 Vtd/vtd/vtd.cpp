#include "vtd.h"

namespace vtd
{
    void vstring::addStr(const char* s)
    {
        int length = strlen(s) + 1;
        str = new char[length];
        strcpy_s(str, length, s);
    }

    void vstring::deleteDRAM()
    {
        if (std::strlen(str) > 0)
            delete[] str;
    }

    vstring::vstring() 
    { 
        str = new char[1];
        strcpy_s(str, 1, "");
    }

    vstring::vstring(const char* s)
    {
        addStr(s);
    }

    vstring::~vstring()
    {
        deleteDRAM();
    }

    void vstring::operator=(const char * s)
    {
        addStr(s);
    }

    void vstring::operator=(const std::string & str_s)
    {
        int length = str_s.size();
        str = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            str[i] = str_s[i];
        }

        str[length] = '\0';
    }

    void vstring::operator=(const vstring & st)
    {
        deleteDRAM();

        int length = strlen(st.str) + 1;
        str = new char[length];
        strcpy_s(str, length, st.str);
    }

    char & vstring::operator[](const int & i)
    {
        int length = strlen(str) - 1;

        if (length > 0 && length >= i)
        {
            return str[i];
        }
    }

    int vstring::size()
    {
        return strlen(str);
    }

    void operator>>(std::istream & is, vstring & st)
    {
        st.deleteDRAM();

        st.str = new char[strlen(st.str) + 1];

        is.getline(st.str, strlen(st.str + 1));
    }

    std::ostream& operator<<(std::ostream & os, const vstring & str)
    {
        os << str.str;

        return os;
    }
}