#ifndef ANALYSER_HPP
#define ANALYSER_HPP

#include "Instruction.hpp"

class Analyser
{
public:
    bool isFromFunctionPrologue(const Instruction& instruction);
    bool isFromFunctionEpilogue(const Instruction& instruction);
};

#endif
