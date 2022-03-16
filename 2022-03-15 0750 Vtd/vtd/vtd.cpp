#include "vtd.h"

namespace vtd
{
    void vstring::addStr(const char* s)
    {
        int length = std::strlen(s);
        str = new char[length + 1];
        std::strcpy(str, s);
    }

    void vstring::deleteDRAM()
    {
        if (std::strlen(str) > 0)
            delete[] str;
    }

    vstring::vstring() 
    { 
        str = new char[1];
        std::strcpy(str, "");
    }

    vstring::vstring(const char* s)
    {
        addStr(s);
    }

    vstring::~vstring()
    {
        deleteDRAM();
    }

    void vstring::operator=(const char* s)
    {
        addStr(s);
    }

    void vstring::operator=(const vstring & st)
    {
        deleteDRAM();

        str = new char[std::strlen(st.str) + 1];
        std::strcpy(str, st.str);
    }

    void operator>>(std::istream& is, vstring& st)
    {
        st.deleteDRAM();

        st.str = new char[std::strlen(st.str) + 1];

        is.getline(st.str, std::strlen(st.str + 1));
    }

    std::ostream& operator<<(std::ostream& os, const vstring& str)
    {
        os << str.str;

        return os;
    }
}