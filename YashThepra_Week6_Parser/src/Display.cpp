#include "Display.h"
#include "Constants.h"

void DisplayParser::displayCSV(const rapidcsv::Document &CSV_Dcoument)
{
    try
    {
        std::cout << Constants::CSV_DOCUMENT;
        int numberOfRows = CSV_Dcoument.GetRowCount();
        int numberOfColumns = CSV_Dcoument.GetColumnCount();
        if (numberOfRows == 0 || numberOfColumns == 0)
        {
            std::cout << Constants::FILE_EMPTY;
            return;
        }
        for (int row = 0; row < numberOfRows; row++)
        {
            for (int column = 0; column < numberOfColumns; column++)
            {
                try
                {
                    std::string value = CSV_Dcoument.GetCell<std::string>(column, row);
                    std::cout << value;
                    if (column < numberOfColumns - 1)
                    {
                        std::cout << Constants::SINGLE_SPACE << Constants::SEPERATION_BAR << Constants::SINGLE_SPACE;
                    }
                }
                catch (const std::exception &exception)
                {
                    std::cout << Constants::EXCEPTION_THROWN << exception.what();
                }
            }

            std::cout << Constants::LINE_SPACE << Constants::LINE_SPACE;
        }

        std::cout << Constants::BORDER_SEPERATOR;
    }
    catch (const std::exception &exception)
    {
        std::cout << Constants::DISPLAY_ERROR << exception.what() << Constants::LINE_SPACE;
    }
    catch (...)
    {
        std::cout << Constants::CSV_DISPLAY_EXCEPTION;
    }
}

void DisplayParser::displayJSON(const nlohmann::ordered_json &JSON_Document)
{
    try
    {
        std::cout << Constants::JSON_DOCUMENT;
        printJSON(JSON_Document, 0);
        std::cout << Constants::BORDER_SEPERATOR;
    }
    catch (const std::exception &exception)
    {
        std::cout << Constants::DISPLAY_ERROR << exception.what() << Constants::LINE_SPACE;
    }
    catch (...)
    {
        std::cout << Constants::JSON_DISPLAY_EXCEPTION;
    }
}

void DisplayParser::printJSON(const nlohmann::ordered_json &node, const int indentation)
{
    std::string spaces(indentation, ' ');
    if (node.is_object())
    {
        nlohmann::ordered_json::const_iterator iterator;

        for (iterator = node.begin(); iterator != node.end(); iterator++)
        {
            std::cout << Constants::LINE_SPACE << spaces << iterator.key() << Constants::COLON;
            if (iterator.value().is_structured())
            {
                std::cout << Constants::LINE_SPACE;
                printJSON(iterator.value(), indentation + 2);
            }
            else
            {
                std::cout << iterator.value() << Constants::LINE_SPACE;
            }
        }
    }
    else if (node.is_array())
    {
        for (int index = 0; index < node.size(); index++)
        {
            printJSON(node[index], indentation + 2);
        }
    }
    else
    {
        std::cout << spaces << node << Constants::LINE_SPACE;
    }
}

void DisplayParser::displayXML(const tinyxml2::XMLDocument &XML_Document)
{
    try
    {
        std::cout << Constants::XML_DOCUMENT;
        const tinyxml2::XMLElement *root = XML_Document.RootElement();
        if (root == nullptr)
        {
            std::cout << Constants::XML_EMPTY_DOCUMENT;
            return;
        }
        printXML(root, 0);
        std::cout << Constants::BORDER_SEPERATOR;
    }
    catch (const std::exception &exception)
    {
        std::cout << Constants::DISPLAY_ERROR << exception.what() << Constants::LINE_SPACE;
    }
    catch (...)
    {
        std::cout << Constants::UNKNOWN_PARSING_EXCEPTION;
    }
}

void DisplayParser::printXML(const tinyxml2::XMLNode *node, const int indentation)
{
    while (node != nullptr)
    {
        const tinyxml2::XMLElement *element = node->ToElement();
        if (element)
        {
            std::string spaces(indentation, ' ');

            std::cout << Constants::LINE_SPACE << spaces << element->Name();
            if (element->GetText())
            {
                std::cout << Constants::COLON2 << element->GetText();
            }
            std::cout << Constants::LINE_SPACE;
        }
        printXML(node->FirstChild(), indentation + 2);
        node = node->NextSibling();
    }
}
