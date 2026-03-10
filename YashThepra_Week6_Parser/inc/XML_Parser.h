#pragma once

#include <tinyxml2.h>

#include "Parser.h"

class XML_Parser : public Parser
{
public:
    XML_Parser(const std::string &fileName);

    bool parseFile() override;

    const tinyxml2::XMLDocument &getDocument() const;

private:
    tinyxml2::XMLDocument XML_Document;
};
