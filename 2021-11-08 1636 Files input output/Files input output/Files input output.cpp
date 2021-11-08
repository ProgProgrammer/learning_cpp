#include <iostream>
#include <fstream>
#include <string>

bool continueInput()
{
    std::string str;
    std::cout << "Continue? y/n: ";
    std::getline(std::cin, str);

    if (str == "n")
    {
        std::cout << "Input terminated.";
        return false;
    }

    if (str != "y")
    {
        std::cout << "Invalid input." << std::endl;
        continueInput();
    }
    else
    {
        std::cout << "Enter file name: ";
    }
}

int main()
{
    std::string output_file = "Write file.txt";
    std::ofstream outFile;
    outFile.open(output_file);
    if (!outFile.is_open())
    {
        std::cout << "Can't open '" << output_file << "' file.";
        return 1;
    }

    std::string input_file;
    std::ifstream inputFile;
    bool check;
    std::string line;

    std::cout << "Enter file name: ";

    while (std::getline(std::cin, input_file))
    {
        inputFile.open(input_file);

        if (!inputFile.is_open())
        {
            std::cout << "Can't open '" << input_file << "' file." << std::endl;

            check = continueInput();

            if (check == false)
            {
                outFile.close();
                return 3;
            }

            continue;
        }

        while (std::getline(inputFile, line))
        {
            outFile << line << std::endl;
        }

        inputFile.close();

        check = continueInput();

        if (check == false)
        {
            outFile.close();
            return 4;
        }
    }

    return 0;
}
