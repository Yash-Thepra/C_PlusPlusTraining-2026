#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <tinyxml2.h>

#include "rapidcsv.h"

class DisplayParser
{
public:
    static void displayCSV(const rapidcsv::Document &doc);

    static void displayJSON(const nlohmann::ordered_json &jsonData);

    static void displayXML(const tinyxml2::XMLDocument &xmlDocument);

private:
    static void printJSON(const nlohmann::ordered_json &node, const int indentation);

    static void printXML(const tinyxml2::XMLNode *node, const int indentation);
};
