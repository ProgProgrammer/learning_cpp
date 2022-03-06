#include "errorfiles.h"

void operator << (std::ofstream& fout, const std::string& error_str)
{
    fout << error_str;
    fout << std::endl;

    std::cout << "OK" << std::endl;
}