#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string input_file_name = "Input file.txt";

    std::ifstream inputFile;
    inputFile.open(input_file_name);

    if (!inputFile.is_open())
    {
        std::cout << "Can't open '" << input_file_name << "' file!";
        return 1;
    }

    std::string output_file = "Write file.txt";

    std::ofstream outFile;
    outFile.open(output_file);

    if (!outFile.is_open())
    {
        std::cout << "Can't open '" << output_file << "' file!";
        return 2;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        outFile << line << std::endl;
    }

    inputFile.close();
    outFile.close();

    return 0;
}