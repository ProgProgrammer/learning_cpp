#include <iostream>
#include "FileManager.h"

FileManager::~FileManager()
{
    ofFile << number_lines << " " << this << std::endl;

    ofFile.close();
}

void FileManager::setFileName(std::string file_name)
{
    fileName = file_name;
}

void FileManager::setBufferLimit(int buffer_lim)
{
    buffer_limit = buffer_lim;
}

void FileManager::writeLine(std::string & str)
{
    if (m_buffer.size() < buffer_limit - 1)
    {
        m_buffer.push_back(str);
    }
    else
    {
        m_buffer.push_back(str);
        flash();
    }
}

void FileManager::flash()
{
    if (!ofFile.is_open())
    {
        ofFile.open(fileName);
    }

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