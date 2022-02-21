#pragma once
#include <vector>
#include <string>
#include <fstream>

class FileManager
{
private:
    int number_lines = 0;
    std::string end_line = "FLASHED";
    std::string fileName;
    std::ofstream ofFile;
    int buffer_limit;
    std::vector<std::string> m_buffer;

public:
    ~FileManager();
    void setFileName(std::string file_name);
    void setBufferLimit(int buffer_lim);
    void writeLine(std::string & str);
    void flash();
};