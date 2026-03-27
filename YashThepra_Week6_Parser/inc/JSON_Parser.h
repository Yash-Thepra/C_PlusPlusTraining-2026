#pragma once

#include <nlohmann/json.hpp>

#include "Parser.h"

class JSON_Parser : public Parser
{
public:
    JSON_Parser(const std::string &fileName);

    bool parseFile() override;

    nlohmann::ordered_json getDocument() const;

private:
    nlohmann::ordered_json JSON_Document;
};
