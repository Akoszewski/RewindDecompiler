#include "Analyser.hpp"

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

bool Analyser::isFromFunctionEpilogue(const Instruction& instruction)
{
    if (instruction.operand == "pop") {
        if (instruction.arguments[0] == "rbp" || instruction.arguments[0] == "ebp") {
            return true;
        }
    } else if (instruction.operand == "ret") {
        return true;
    }
    return false;
}
