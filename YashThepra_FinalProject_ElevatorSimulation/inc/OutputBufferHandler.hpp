#pragma once

#include <cerrno>
#include <streambuf>
#include <unistd.h>
#include <vector>

class OutputBufferHandler : public std::streambuf
{
public:
    OutputBufferHandler(int fileDescriptor)
        : fileDescriptor{fileDescriptor}
    {
        buffer.resize(8192);
        setp(buffer.data(), buffer.data() + buffer.size() - 1);
    }

protected:
    int overflow(const int character) override
    {
        if (character != traits_type::eof())
        {
            *pptr() = static_cast<char>(character);
            pbump(1);
        }
        return flushBuffer() ? character : traits_type::eof();
    }

    int sync() override
    {
        return flushBuffer() ? 0 : -1;
    }

private:
    bool flushBuffer()
    {
        const std::ptrdiff_t length = pptr() - pbase();
        if (length <= 0)
        {
            return true;
        }
        ::write(fileDescriptor, pbase(), static_cast<std::size_t>(length));
        pbump(static_cast<int>(-length));
        return true;
    }
    
    int                fileDescriptor;
    std::vector<char>  buffer;
};
