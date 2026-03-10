#pragma once

#include <string>

namespace Constants
{
    const int minimum = 1;
    const int maximum = 4;
    const std::string BORDER_SEPERATOR = "\n================================\n";
    const std::string COLON = ":";
    const std::string COLON2 = " : ";
    const std::string CSV_DOCUMENT = "\n=========== CSV DOCUMENT ===========\n\n";
    const std::string CSV_DISPLAY_EXCEPTION = "\nUnknown CSV display error\n";
    const std::string CSV_PARSE_ERROR = "Can't Parse CSV file.\n";
    const std::string DATA_FOLDER = "data/";
    const std::string DISPLAY_ERROR = "\nDisplay error occurred.\n";
    const std::string ENTER_CHOICE = "Enter your choice: ";
    const std::string ENTER_FILENAME = "\nEnter file name: ";
    const std::string EXCEPTION_THROWN = "\nthrown exception is: ";
    const std::string  EXIT_PROGRAM = "\nExiting Program....\n";
    const std::string FILE_EMPTY = "\nError: File is empty.\n";
    const std::string FILE_NOT_FOUND = "\nError: File not found.\n";
    const std::string INVALID_INPUT = "\nError: Invalid input. Please try again.\n";
    const std::string INVALID_JSON_STRUCTURE = "\nThe structure of JSON Document is invalid.\n";
    const std::string JSON_DOCUMENT = "\n=========== JSON DOCUMENT ===========\n\n";
    const std::string JSON_DISPLAY_EXCEPTION = "\nUnknow json display error.\n";
    const std::string JSON_PARSE_ERROR = "\nJSON parsing failed.\n";
    const std::string LINE_SPACE = "\n";
    const std::string MAIN_MENU =
        "===============================\n"
        "        Parser Program\n"
        "===============================\n"
        "1. Parse JSON File\n"
        "2. Parse CSV File\n"
        "3. Parse XML File\n"
        "4. Exit\n"
        "===============================\n";
    const std::string SEPERATION_BAR = "|";
    const std::string SINGLE_SPACE = " ";
    const std::string SPACES = "   ";
    const std::string UNKNOWN_PARSING_EXCEPTION = "\nUnknown XML parsing error\n";
    const std::string XML_DOCUMENT = "\n=========== XML DATA ===========\n\n";
    const std::string XML_DISPLAY_EXCEPTION = "\nUnknown xml display error.\n";
    const std::string XML_PARSE_ERROR = "\ncan't pares XML file.\n";
    const std::string XML_EMPTY_DOCUMENT = "\nThe XML Document is empty.\n";
}
