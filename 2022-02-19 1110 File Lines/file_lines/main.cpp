#include <iostream>
#include "FileManager.h"

int main()
{
    std::string val;
    std::string fileName = "default.txt";
    int bufferLimit = 1;
    bool file_name = false;
    bool buffer_limit = false;

    std::cout << "Do you want to enter a file name?(y/n) ";
    std::getline(std::cin, val);

    FileManager fileManager;

    if (val == "y")
    {
        std::cout << "Enter name file: ";
        std::getline(std::cin, fileName);
        fileManager.setFileName(fileName);
        file_name = true;
    }
    else
    {
        fileManager.setFileName(fileName);
    }

    std::cout << "Do you want to enter a lines limit?(y/n) ";
    std::getline(std::cin, val);

    if (val == "y")
    {
        std::cout << "Enter line limit: ";
        std::cin >> bufferLimit;
        fileManager.setBufferLimit(bufferLimit);
        buffer_limit = true;
    }
    else
    {
        fileManager.setBufferLimit(bufferLimit);
    }

    std::vector<std::string> arr_str = { "line", "hello", "asdf", "bob", "qwer", "asdf", "asdfa", "kjlkj", 
                                        "qwer", "jojoeijrf" };

    for (int i = 0; i < arr_str.size(); i++)
    {
        fileManager.writeLine(arr_str[i]);

        if (i + 1 == arr_str.size() && arr_str.size() % bufferLimit != 0)
        {
            fileManager.flash();
        }
    }

    return 0;
}