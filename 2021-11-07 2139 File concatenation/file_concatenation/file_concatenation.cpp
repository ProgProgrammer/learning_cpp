#include <iostream>
#include <fstream>
#include <string>

// how to use:
// file_concatenation.exe Input_file.txt Input_file2.txt Input_file3.txt

int main(int argc, char* argv[])
{
    std::string output_file = "Write file.txt";
    std::ofstream outFile;

    outFile.open(output_file);

    if (outFile.is_open())
    {
        std::string line;

        for (int i = 0; i < argc; i++)
        {
            if (i > 0)
            {
                std::ifstream inFile;
                inFile.open(argv[i]);
                if (inFile.is_open())
                {
                    while (std::getline(inFile, line))
                    {
                        outFile << line << std::endl;
                    }
                }
                else
                {
                    std::cout << "Can't open '" << argv[i] << "' file.";
                    return 2;
                }
                inFile.close();
            }
        }
    }
    else
    {
        std::cout << "Can't open '" << output_file << "' file.";
        return 1;
    }

    outFile.close();
    return 0;
}