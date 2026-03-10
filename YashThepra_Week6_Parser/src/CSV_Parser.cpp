#include <fstream>
#include <iostream>

#include "Constants.h"
#include "CSV_Parser.h"

CSV_Parser::CSV_Parser(const std::string &fileName)
{
    this->fileName = fileName;
}

bool CSV_Parser::parseFile()
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
        if (file.peek() == std::ifstream::traits_type::eof())
        {
            std::cout << Constants::FILE_EMPTY;
            isValidFile = false;
        }
        CSV_Document = rapidcsv::Document(std::string(Constants::DATA_FOLDER) + fileName);
        isValidFile = true;
    }
    catch (const std::exception &exception)
    {
        std::cout << Constants::CSV_PARSE_ERROR << exception.what() << Constants::LINE_SPACE;
        isValidFile = false;
    }
    catch (...)
    {
        std::cout << Constants::UNKNOWN_PARSING_EXCEPTION;
        isValidFile = false;
    }
    return isValidFile;
}

rapidcsv::Document CSV_Parser::getDocument() const
{
    return CSV_Document;
}
