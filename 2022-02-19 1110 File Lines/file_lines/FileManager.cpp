#include <iostream>
#include "FileManager.h"

FileManager::FileManager(values vals)
{
    ofFile.open(vals.fileName);
    buffer_limit = vals.bufferLimit - 1;
}

FileManager::~FileManager()
{
    ofFile << number_lines << " " << this << std::endl;

    ofFile.close();
}

void FileManager::writeLine(std::string & str)
{
    if (arr_elements < buffer_limit)
    {
        m_buffer.push_back(str);
        arr_elements++;
    }
    else
    {
        m_buffer.push_back(str);
        arr_elements = 0;
        flash();
    }
}

void FileManager::flash()
{
    if (ofFile.is_open() && m_buffer.size() > 0)
    {
        for (int i = 0; i < m_buffer.size(); i++)
        {
            ofFile << m_buffer[i] << std::endl;
            number_lines++;
        }

        ofFile << end_line << std::endl;

        m_buffer.clear();
    }
}