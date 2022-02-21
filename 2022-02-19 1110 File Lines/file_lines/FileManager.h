#pragma once
#include <vector>
#include <string>
#include <fstream>

class FileManager
{
private:
    int m_numberLines = 0;
    std::string m_endLine = "FLASHED";
    std::string m_fileName = "default.txt";
    std::ofstream m_ofFile;
    int m_bufferLimit = 1;
    std::vector<std::string> m_buffer;

public:
    ~FileManager();
    void setFileName(std::string fileName);
    void setBufferLimit(int bufferLimit);
    void writeLine(std::string & str);
    void flash();
};