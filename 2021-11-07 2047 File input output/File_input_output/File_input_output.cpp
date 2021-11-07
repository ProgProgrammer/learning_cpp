#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string file_name = "Input file.txt";

    std::ifstream inputFile;
    inputFile.open(file_name);

    if (!inputFile.is_open())
    {
        return 1;
    }

    std::ofstream outFile;
    outFile.open("Write file.txt");

    if (!outFile.is_open())
    {
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