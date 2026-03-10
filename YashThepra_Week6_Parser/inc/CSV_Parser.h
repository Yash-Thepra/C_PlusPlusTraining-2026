#pragma once

#include "Parser.h"
#include "rapidcsv.h"

class CSV_Parser : public Parser
{
public:
    CSV_Parser(const std::string &fileName);

    bool parseFile() override;

    rapidcsv::Document getDocument() const;

private:
    rapidcsv::Document CSV_Document;
};
