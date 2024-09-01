#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "Instruction.hpp"
#include "Variable.hpp"

#include <string>
#include <map>

struct Function
{
    int address;
    std::string type;
    std::string name;
    std::vector<Instruction> instructions;
    std::vector<Variable> parameters;
    bool isDllTrampoline;
    std::map<std::string, std::string> aliasMap;
};

#endif
