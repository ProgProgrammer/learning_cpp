#include <iostream>
#include "FileManager.h"

int main()
{
    std::string val;
    bool file_name = false;
    bool buffer_limit = false;

    values vals;

    std::cout << "Do you want to enter a file name?(y/n) ";
    std::getline(std::cin, val);

    if (val == "y")
    {
        std::cout << "Enter name file: ";
        std::getline(std::cin, vals.fileName);
        file_name = true;
    }

    std::cout << "Do you want to enter a lines limit?(y/n) ";
    std::getline(std::cin, val);

    if (val == "y")
    {
        std::cout << "Enter line limit: ";
        std::cin >> vals.bufferLimit;
        buffer_limit = true;
    }

    FileManager * File_M = new FileManager(vals);

    std::string str;
    std::string action;

    std::cout << "Enter line: ";

    if (file_name == false || buffer_limit == true)
    {
        std::cin.ignore();
    }

    while(std::getline(std::cin, str))
    {
        File_M->writeLine(str);

        std::cout << "Still want to write a line(y/n): ";
        std::cin >> action;

        if (action == "n")
        {
            File_M->flash();
            break;
        }

        std::cout << "Enter line: ";
        std::cin.ignore();
    }

    delete File_M;

    return 0;
}