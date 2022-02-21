#include "FileManager.h"

FileManager::~FileManager()
{
    m_ofFile << m_numberLines << " " << this << std::endl;

    m_ofFile.close();
}

void FileManager::setFileName(std::string file_name)
{
    m_fileName = file_name;
}

void FileManager::setBufferLimit(int buffer_lim)
{
    m_bufferLimit = buffer_lim;
}

void FileManager::writeLine(std::string & str)
{
    if (m_buffer.size() < m_bufferLimit - 1)
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
    if (!m_ofFile.is_open())
    {
        m_ofFile.open(m_fileName);
    }

    if (m_ofFile.is_open() && m_buffer.size() > 0)
    {
        for (int i = 0; i < m_buffer.size(); i++)
        {
            m_ofFile << m_buffer[i] << std::endl;
            m_numberLines++;
        }

        if (m_numberLines >= m_bufferLimit)
        {
            m_ofFile << m_endLine << std::endl;
        }

        m_buffer.clear();
    }
}