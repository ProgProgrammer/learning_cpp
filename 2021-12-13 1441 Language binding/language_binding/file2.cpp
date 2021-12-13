#include <iostream>
#include "header.h"

extern "C" void coutString(std::string str);

void output()
{
    std::string str = "Hi!";

    coutString(str);
}