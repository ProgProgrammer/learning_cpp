#include <iostream>
#include "FileManager.h"

int main()
{
    std::string val;

    std::cout << "Do you want to enter a file name?(y/n) ";
    std::getline(std::cin, val);

    FileManager fileManager;

    if (val == "y")
    {
        std::string fileName = "default.txt";
        std::cout << "Enter name file: ";
        std::getline(std::cin, fileName);
        fileManager.setFileName(fileName);
    }

    std::cout << "Do you want to enter a lines limit?(y/n) ";
    std::getline(std::cin, val);

    if (val == "y")
    {
        int bufferLimit = 1;
        std::cout << "Enter line limit: ";
        std::cin >> bufferLimit;
        fileManager.setBufferLimit(bufferLimit);
    }

    for (int i = 0; i < 100; i++)
    {
        std::string line = "line_" + std::to_string(i);
        fileManager.writeLine(line);
    }

    return 0;
}