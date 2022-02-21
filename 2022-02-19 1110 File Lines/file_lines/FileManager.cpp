#include "FileManager.h"

FileManager::~FileManager()
{
    if (!m_buffer.empty())
    {
        flash();
    }

    m_ofFile << m_numberLines << " " << this << std::endl;

    m_ofFile.close();
}

void FileManager::setFileName(std::string fileName)
{
    m_fileName = fileName;
}

void FileManager::setBufferLimit(int bufferLimit)
{
    m_bufferLimit = bufferLimit;
}

void FileManager::writeLine(std::string & str)
{
    m_buffer.push_back(str);

    if (m_buffer.size() > m_bufferLimit)
    {
        flash();
    }
}

void FileManager::flash()
{
    if(m_buffer.empty())
    {
        return;
    }

    if (!m_ofFile.is_open())
    {
        m_ofFile.open(m_fileName);
    }

    for (int i = 0; i < m_buffer.size(); i++)
    {
        m_ofFile << m_buffer[i] << std::endl;
        m_numberLines++;
    }

    m_ofFile << m_endLine << std::endl;

    m_buffer.clear();
}