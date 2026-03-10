#include <iostream>

#include "Constants.h"
#include "CSV_Parser.h"
#include "Display.h"
#include "input.h"
#include "JSON_Parser.h"
#include "XML_Parser.h"

int runApplication()
{
    while (true)
    {
        std::cout << Constants::MAIN_MENU;
        int choice = Input::readMenuChoice(Constants::minimum, Constants::maximum);

        if (choice == 4)
        {
            std::cout << Constants::EXIT_PROGRAM;
            break;
        }
        std::cout << Constants::ENTER_FILENAME;
        std::string fileName = Input::readNonEmptyString();
        if (choice == 1)
        {
            JSON_Parser parser(fileName);
            if (parser.parseFile())
            {
                DisplayParser::displayJSON(parser.getDocument());
            }
        }
        else if (choice == 2)
        {
            CSV_Parser parser(fileName);
            if (parser.parseFile())
            {
                DisplayParser::displayCSV(parser.getDocument());
            }
        }
        else if (choice == 3)
        {
            XML_Parser parser(fileName);
            if (parser.parseFile())
            {
                DisplayParser::displayXML(parser.getDocument());
            }
        }
    }
    return 0;
}
