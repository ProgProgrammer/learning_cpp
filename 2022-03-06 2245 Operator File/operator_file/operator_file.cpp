#include <fstream>
#include <string>
#include "errorfiles.h"

int main()
{
    ErrorFiles error_file;
    std::ofstream fout;
    std::string str;

    fout.open("error_file.txt");

    std::cout << "Enter words: ";

    while (std::getline(std::cin, str))
    {
        if (fout.is_open())
        {
            fout << str;

            std::cout << "Enter words?(y/n) ";
            std::getline(std::cin, str);

            if (str == "n")
            {
                break;
            }

            std::cout << "Enter words: ";
        }
        else
        {
            fout.open("error_file.txt");
        }
    }

    fout.close();

    std::cout << "Good buy!";
}