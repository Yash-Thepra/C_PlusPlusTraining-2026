#include <fstream>
#include <iostream>

#include "Constants.h"
#include "JSON_Parser.h"

JSON_Parser::JSON_Parser(const std::string &fileName)
{
    this->fileName = fileName;
}

bool JSON_Parser::parseFile()
{
    bool isValidFile = true;
    std::ifstream file(std::string(Constants::DATA_FOLDER) + fileName);
    try
    {
        if (!file.is_open())
        {
            std::cout << Constants::FILE_NOT_FOUND;
            isValidFile = false;
        }
        else if (file.peek() == std::ifstream::traits_type::eof())
        {
            std::cout << Constants::FILE_EMPTY;
            isValidFile = false;
        }
        else
        {
            file >> JSON_Document;
        }
    }
    catch (const nlohmann::json::parse_error &exception)
    {
        std::cout << Constants::JSON_PARSE_ERROR << exception.what() << Constants::LINE_SPACE;
        isValidFile = false;
    }
    catch (const std::exception &exception)
    {
        std::cout << Constants::JSON_PARSE_ERROR << exception.what() << Constants::LINE_SPACE;
        isValidFile = false;
    }
    catch (...)
    {
        std::cout << Constants::UNKNOWN_PARSING_EXCEPTION;
        isValidFile = false;
    }
    return isValidFile;
}

nlohmann::ordered_json JSON_Parser::getDocument() const 
{
    return JSON_Document;
}
