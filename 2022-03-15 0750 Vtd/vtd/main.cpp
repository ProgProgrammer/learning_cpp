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

    vst2 = vst3;
    std::cout << vst2 << std::endl;

    vst3 = str;
    std::cout << vst3 << std::endl;

    char str_c[12] = "Hello, Ann!";
    vtd::vstring vst4, vst5, vst6, vst7;

    vst4 = str_c;
    std::cout << vst4 << std::endl;

    char name1[] = "helloPeople";
    vst4 = name1;
    std::cout << vst4 << std::endl;

    std::string str2 = "Hello, Denis!";

    vst5 = str2;
    std::cout << vst5 << std::endl;

    vst6 = "Hi!";
    std::cout << vst6 << std::endl;
    vst6[2] = str2[1];
    std::cout << vst6 << std::endl;

    std::cout << vst6.size() << std::endl;

    char str_c2[6] = "Hello";
    vst7 = "Good";

    str_c2[0] = vst7[0];

    std::cout << str_c2 << std::endl;

    return 0;
}