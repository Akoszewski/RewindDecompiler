#include "Analyser.hpp"
#include "Parser.hpp"

#include <iostream>

bool Analyser::isFromFunctionPrologue(const Instruction& instruction)
{
    if (instruction.operand == "push") {
        if (instruction.arguments[0] == "rbp" || instruction.arguments[0] == "ebp") {
            return true;
        }
    } else if (instruction.operand == "mov") {
        if (instruction.arguments[0] == "rbp" && instruction.arguments[1] == "rsp") {
            return true;
        } else if (instruction.arguments[0] == "ebp" && instruction.arguments[1] == "esp") {
            return true;
        }
    }
    return false;
}

bool Analyser::isFromFunctionEpilogueExceptRet(const Instruction& instruction)
{
    if (instruction.operand == "pop") {
        if (instruction.arguments[0] == "rbp" || instruction.arguments[0] == "ebp") {
            return true;
        }
    }
    if (instruction.operand == "leave") {
        return true;
    }
    return false;
}

std::optional<Function> Analyser::findFunctionWithAddress(int address)
{
    std::optional<Function> result;
    for (const auto& f : Parser::getInstance().functions)
    {
        if (f.address == address) {
            result = std::optional(f);
        }
    }
    return result;
}
