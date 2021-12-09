#include <iostream>

struct stringy
{
    char* str;
    int ct;
};

char * set(stringy& box, char* testing)
{
    int size = strlen(testing);
    char* const str_ch = new char[size + 1];

    for (int i = 0; i < strlen(testing); i++)
    {
        str_ch[i] = testing[i];
    }

    str_ch[size] = '\0';
    box.str = str_ch;
    box.ct = strlen(testing) - 1;

    return str_ch;
}

void show(const stringy& box, const int n = 1)
{
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

    delete[] pointer;

    testing[0] = 'D';
    testing[1] = 'u';

    show(testing);
    show(testing, 3);
    show("Done!");

    return 0;
}
