#pragma once
#include <iostream>

namespace vtd
{
    class vstring
    {
    private:
        char * str;
        void addStr(const char * s);
        void deleteDRAM();

    public:
        vstring();
        vstring(const char * s);
        ~vstring();

        void operator=(const char * s);
        void operator=(const std::string & str_s);
        void operator=(const vstring & st);
        char & operator[](const int & i);
        int size();

        friend void operator>>(std::istream & is, vstring & st);
        friend std::ostream& operator<<(std::ostream & os, const vstring & str);
    };
}