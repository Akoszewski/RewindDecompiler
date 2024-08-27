#include "Analyser.hpp"
#include "Parser.hpp"

#include <iostream>
#include <algorithm>

Analyser::Analyser()
{
    parameterRegisters = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    registerMap = {
        {"rax", Register("eax", "ax", "al", "ah")},
        {"rbx", Register("ebx", "bx", "bl", "bh")},
        {"rcx", Register("ecx", "cx", "cl", "ch")},
        {"rdx", Register("edx", "dx", "dl", "dh")},
        {"rdi", Register("edi", "di", "dil", "")},
        {"rsi", Register("esi", "si", "sil", "")},
        {"rbp", Register("ebp", "bp", "bpl", "")},
        {"rsp", Register("esp", "sp", "spl", "")},
        {"r8",  Register("r8d", "r8w", "r8b", "")},
        {"r9",  Register("r9d", "r9w", "r9b", "")},
        {"r10", Register("r10d", "r10w", "r10b", "")},
        {"r11", Register("r11d", "r11w", "r11b", "")},
        {"r12", Register("r12d", "r12w", "r12b", "")},
        {"r13", Register("r13d", "r13w", "r13b", "")},
        {"r14", Register("r14d", "r14w", "r14b", "")},
        {"r15", Register("r15d", "r15w", "r15b", "")},
    };
}

std::string Analyser::getParentRegisterName(const std::string& regName)
{
    for (const auto& registerRecord : registerMap)
    {
        if (registerRecord.first == regName) {
            return registerRecord.first;
        }
        if (registerRecord.second.dwordVersionName == regName) {
            return registerRecord.first;
        }
        else if (registerRecord.second.wordVersionName == regName) {
            return registerRecord.first;
        }
        else if (registerRecord.second.byteVersionName == regName) {
            return registerRecord.first;
        }
        else if (registerRecord.second.highByteVersionName == regName) {
            return registerRecord.first;
        }
    }
    return std::string{};
}

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

bool isElementInVectorOfStrings(std::string el, std::vector<std::string> vecOfStr)
{
    return std::find(vecOfStr.begin(), vecOfStr.end(), el) != vecOfStr.end();
}

bool Analyser::isParameterRegister(const std::string& regName)
{
    std::string parentRegName = getParentRegisterName(regName);
    for (const auto& pmRegName : parameterRegisters)
    {
        if (pmRegName == parentRegName) {
            return true;
        }
    }
    return false;
}

void Analyser::initFunctionParameters(Function& function)
{
    int parameterCounter = 1;
    for (const auto& instr : function.instructions)
    {
        if (instr.arguments.empty()) {
            continue;
        }
        if (isParameterRegister(instr.arguments[0])) {
            registerMap[getParentRegisterName(instr.arguments[0])].wasChanged = true;
        }

        if (instr.operand == "mov") {
            if (isParameterRegister(instr.arguments[1])) {
                if (!registerMap[getParentRegisterName(instr.arguments[1])].wasChanged) {
                    function.parameters.push_back(Variable{"int", "arg" + parameterCounter}); // TODO: find also a type
                    parameterCounter++;
                }
            }
        }
    }
}
