#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "Instruction.hpp"
#include "Variable.hpp"

#include <string>

struct Function
{
    int address;
    std::string type;
    std::string name;
    std::vector<Instruction> instructions;
    std::vector<Variable> parameters;
    bool isDllTrampoline;
};

#endif
