#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <string>
#include <vector>

struct Instruction
{
    int address;
    std::string operand;
    std::vector<std::string> arguments;
};

#endif
