#pragma once

#include <string>

class Parser
{
public:
    virtual bool parseFile() = 0;

    virtual ~Parser() {}

protected:
    std::string fileName;
};
