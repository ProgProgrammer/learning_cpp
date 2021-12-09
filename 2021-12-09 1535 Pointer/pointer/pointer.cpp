#include <iostream>

struct stringy
{
    char* str;
    int ct;
};

auto set(stringy& box, char* testing)
{
    int size = strlen(testing);
    char* const str_ch = new char[size];
    std::cout << strlen(testing) << std::endl;
    std::cout << strlen(str_ch) << std::endl;

    for (int i = 0; i < strlen(testing); i++)
    {
        str_ch[i] = testing[i];
    }

    box.str = str_ch;
    std::cout << strlen(box.str) << std::endl;
    box.ct = strlen(testing) - 1;

    return str_ch;
}

void show(const stringy& box, const int n = 1)
{
    std::cout << strlen(box.str) << std::endl;

    for (int i = 0; i < n; i++)
    {
        std::cout << box.str << std::endl;
    }
}

void show(const char* str, const int n = 1)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << str << std::endl;
    }
}

int main()
{
    stringy beany;
    char testing[] = "Reality isn't what it used to be.";

    auto pointer = set(beany, testing);
    show(beany);
    show(beany, 2);

    testing[0] = 'D';
    testing[1] = 'u';

    show(testing);
    show(testing, 3);
    show("Done!");

    delete[] pointer;

    return 0;
}
