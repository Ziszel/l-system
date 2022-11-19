#include "../include/rule.hpp"

Rule::Rule(char i, std::string o)
{
    input = i;
    output = o;
}

char Rule::Get_Input() {
    return input;
}

std::string Rule::Get_Output() {
    return output;
}