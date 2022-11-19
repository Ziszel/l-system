#pragma once
#include <string>

class Rule {
private:
    char input;
    std::string output;

public:
    Rule(char i, std::string o);
    char Get_Input();
    std::string Get_Output();
};
