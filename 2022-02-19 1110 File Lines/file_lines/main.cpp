#include <iostream>
#include "FileManager.h"

int main()
{
    std::string val;
    std::string fileName = "";
    int bufferLimit = 1;
    bool file_name = false;
    bool buffer_limit = false;

    std::cout << "Do you want to enter a file name?(y/n) ";
    std::getline(std::cin, val);

    FileManager File_M;

    if (val == "y")
    {
        std::cout << "Enter name file: ";
        std::getline(std::cin, fileName);
        File_M.setFileName(fileName);
        file_name = true;
    }
    else
    {
        File_M.setFileName();
    }

    std::cout << "Do you want to enter a lines limit?(y/n) ";
    std::getline(std::cin, val);

    if (val == "y")
    {
        std::cout << "Enter line limit: ";
        std::cin >> bufferLimit;
        File_M.setBufferLimit(bufferLimit);
        buffer_limit = true;
    }
    else
    {
        File_M.setBufferLimit();
    }

    std::vector<std::string> arr_str = { "line", "hello", "asdf", "bob", "qwer", "asdf", "asdfa", "kjlkj", 
                                        "qwer", "jojoeijrf" };

    for (int i = 0; i < arr_str.size(); i++)
    {
        File_M.writeLine(arr_str[i]);

        if (i + 1 == arr_str.size() && arr_str.size() % bufferLimit != 0)
        {
            File_M.flash();
        }
    }

    return 0;
}