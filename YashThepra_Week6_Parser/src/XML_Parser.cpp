#include <iostream>

#include "Constants.h"
#include "XML_Parser.h"

XML_Parser::XML_Parser(const std::string &fileName)
{
    this->fileName = fileName;
}

bool XML_Parser::parseFile()
{
    bool isValidFile = true;
    try
    {
        tinyxml2::XMLError error = XML_Document.LoadFile((std::string(Constants::DATA_FOLDER) + fileName).c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            std::cout << Constants::XML_PARSE_ERROR;
            std::cout << XML_Document.ErrorStr() << Constants::LINE_SPACE;
            isValidFile = false;
        }
    }
    catch (const std::exception &exception)
    {
        std::cout << Constants::XML_PARSE_ERROR << exception.what() << Constants::LINE_SPACE;
        isValidFile = false;
    }
    catch (...)
    {
        std::cout << Constants::UNKNOWN_PARSING_EXCEPTION;
        isValidFile = false;
    }
    return isValidFile;
}

const tinyxml2::XMLDocument &XML_Parser::getDocument() const
{
    return XML_Document;
}
