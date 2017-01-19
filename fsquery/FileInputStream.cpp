
#include "FileInputStream.h"
#include "FSQueryException.h"

#include <cstring>
#include <iostream>

FileInputStream::FileInputStream(const std::string& path)
: m_currentPosition(0), m_beforeStart(true)
{
    m_ifstream.open(path, std::ifstream::binary);
	
	if (!m_ifstream.good())
	{
		throw FSQueryException("FileInputStream: Could not open file '" + path + "'");
	}
	
	m_streamSize = ComputeStreamSize();
}

bool FileInputStream::HasNext() const /* override */
{
    return (m_beforeStart && m_streamSize > 0) || m_currentPosition + 1 < m_streamSize;
}

char FileInputStream::GetNext() /* override */
{
    if (m_beforeStart)
    {
        // no need to advance m_currentPosition as it already points to the first character
        m_beforeStart = false;
    }
    else
    {
        ++m_currentPosition;
    }
    
    if (IsTimeToReadNextPage())
    {
        ReadNextPage();
    }
    
    return m_buffer[m_currentPosition % FILE_INPUT_STREAM_BUFFER_SIZE];
}

size_t FileInputStream::ComputeStreamSize()
{
    m_ifstream.seekg(0, std::ios::end);
    size_t streamSize = m_ifstream.tellg();
    m_ifstream.seekg(0, std::ios::beg);
    return streamSize;
}

bool FileInputStream::IsTimeToReadNextPage()
{
    return m_currentPosition % FILE_INPUT_STREAM_BUFFER_SIZE == 0;
}

void FileInputStream::ReadNextPage()
{
    m_ifstream.read(m_buffer, FILE_INPUT_STREAM_BUFFER_SIZE);
}
