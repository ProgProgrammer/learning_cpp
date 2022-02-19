#pragma once
#include <vector>
#include <string>
#include <fstream>
#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

struct values
{
    std::string fileName = "default.txt";
    int bufferLimit = 1;
};

class FileManager
{
private:
    int arr_elements = 0;
    int number_lines = 0;
    std::string end_line = "FLASHED";
    std::ofstream ofFile;
    int buffer_limit;
    std::vector<std::string> m_buffer;

public:
    FileManager(values vals);
    ~FileManager();
    void writeLine(std::string & str);
    void flash();
};

#endif