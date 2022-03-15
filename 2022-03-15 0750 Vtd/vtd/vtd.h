#pragma once
#pragma warning(disable : 4996);
#include <iostream>

namespace vtd
{
    class vstring
    {
    private:
        char* str;
        void addStr(const char* s);
        void deleteDRAM();

    public:
        vstring();
        vstring(const char* s);
        ~vstring();

        void operator=(const char* s);
        void operator=(const vstring& str);
        friend void operator>>(std::istream& is, vstring& st);
        friend std::ostream& operator<<(std::ostream& os, const vstring& str);
    };
}