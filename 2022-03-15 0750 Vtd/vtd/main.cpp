#include "vtd.h"

int main()
{
    vtd::vstring str = "Hello, world!";

    std::cout << "1" << str << std::endl;
    std::cin >> str;
    std::cout << "2" << str << std::endl;

    str = "Hello, Sergey!";

    std::cout << "3" << str << std::endl;

    vtd::vstring vst;
    std::cout << vst << std::endl;

    vtd::vstring vst2 = "";
    std::cout << vst2 << std::endl;

    vtd::vstring vst3 = "Hi!";
    std::cout << vst3 << std::endl;

    return 0;
}