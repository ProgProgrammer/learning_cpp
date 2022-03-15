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

    public:
        vstring();
        vstring(const char* s);
        ~vstring();

        void operator=(const char* s);
        friend void operator>>(std::istream& is, vstring& str);
        friend std::ostream& operator<<(std::ostream& os, const vstring& str);
    };
}