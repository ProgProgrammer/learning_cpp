#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    std::string output_file = "Write file.txt";
    std::ofstream outFile;

    outFile.open(output_file);

    if (outFile.is_open())
    {
        std::string line;

        std::ifstream inFile;

        for (int i = 0; i < argc; i++)
        {
            if (i > 0)
            {
                std::string str = argv[i];
                std::cout << typeid(str).name() << std::endl;
                inFile.open(str);
                if (inFile.is_open())
                {
                    while (std::getline(inFile, line))
                    {
                        outFile << line << std::endl;
                    }
                }
                else
                {
                    std::cout << "Can't open '" << str << "' file.";
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