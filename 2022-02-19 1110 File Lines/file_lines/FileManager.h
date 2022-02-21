#pragma once
#include <vector>
#include <string>
#include <fstream>

class FileManager
{
private:
    int m_numberLines = 0;
    std::string m_endLine = "FLASHED";
    std::string m_fileName;
    std::ofstream m_ofFile;
    int m_bufferLimit;
    std::vector<std::string> m_buffer;

public:
    ~FileManager();
    void setFileName(std::string file_name);
    void setBufferLimit(int buffer_lim);
    void writeLine(std::string & str);
    void flash();
};