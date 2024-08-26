#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <string>
#include <vector>

struct InstructionInitializationTempData
{
    bool isAddressInitialized = false;
    bool isHexBytesPassed = false;
    bool isOperandRead = false;
    std::string argumentsStr;
};

struct Instruction
{
    int address;
    std::string operand;
    std::vector<std::string> arguments;
};

#endif
