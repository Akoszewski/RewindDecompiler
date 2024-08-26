#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "Instruction.hpp"

#include <string>

struct Function
{
    std::string name;
    std::vector<Instruction> instructions;
};

#endif
