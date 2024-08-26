#ifndef ANALYSER_HPP
#define ANALYSER_HPP

#include "Function.hpp"

#include <optional>

enum class RegStatus
{
    Unknown,
    IsKnownNumber,
    IsEqualToOtherUnit
};

struct Register
{
    RegStatus status = RegStatus::Unknown;
    long long value = 0;
};

class Analyser
{
public:
    bool isFromFunctionPrologue(const Instruction& instruction);
    bool isFromFunctionEpilogueExceptRet(const Instruction& instruction);
    std::optional<Function> findFunctionWithAddress(int address);
    Register rax;
};

#endif
