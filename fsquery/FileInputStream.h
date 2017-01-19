
#ifndef FILEINPUTSTREAM_H
#define FILEINPUTSTREAM_H

#include "InputStream.h"

#include <string>
#include <fstream>

#define FILE_INPUT_STREAM_BUFFER_SIZE 5

class FileInputStream : public InputStream
{
public:
    FileInputStream(const std::string& path);

    virtual bool HasNext() const override;
    virtual char GetNext() override;
    
private:
    size_t ComputeStreamSize();
    bool IsTimeToReadNextPage();
    void ReadNextPage();

    std::ifstream m_ifstream;
    char m_buffer[FILE_INPUT_STREAM_BUFFER_SIZE];
    size_t m_currentPosition;
    size_t m_streamSize;
    bool m_beforeStart;
};

#endif // FILEINPUTSTREAM_H
