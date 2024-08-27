#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "Instruction.hpp"

#include <string>

struct Function
{
    int address;
    std::string name;
    std::vector<Instruction> instructions;
    bool isDllTrampoline;
};

#endif
