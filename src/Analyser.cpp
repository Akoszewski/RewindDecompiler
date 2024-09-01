#include "Analyser.hpp"
#include "Parser.hpp"

#include <iostream>
#include <algorithm>

Analyser::Analyser()
{
    parameterRegisters = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};

    sizeToTypeMap = {
        {1, "char"},
        {2, "short"},
        {4, "int"},
        {8, "long long"},
    };

    registerMap = {
        {"rax", Register(8, "rax", "eax", "ax", "al", "ah")},
        {"rbx", Register(8, "rbx", "ebx", "bx", "bl", "bh")},
        {"rcx", Register(8, "rcx", "ecx", "cx", "cl", "ch")},
        {"rdx", Register(8, "rdx", "edx", "dx", "dl", "dh")},
        {"rdi", Register(8, "rdi", "edi", "di", "dil", "")},
        {"rsi", Register(8, "rsi", "esi", "si", "sil", "")},
        {"rbp", Register(8, "rbp", "ebp", "bp", "bpl", "")},
        {"rsp", Register(8, "rsp", "esp", "sp", "spl", "")},
        {"r8",  Register(8, "r8", "r8d", "r8w", "r8b", "")},
        {"r9",  Register(8, "r9", "r9d", "r9w", "r9b", "")},
        {"r10", Register(8, "r10", "r10d", "r10w", "r10b", "")},
        {"r11", Register(8, "r11", "r11d", "r11w", "r11b", "")},
        {"r12", Register(8, "r12", "r12d", "r12w", "r12b", "")},
        {"r13", Register(8, "r13", "r13d", "r13w", "r13b", "")},
        {"r14", Register(8, "r14", "r14d", "r14w", "r14b", "")},
        {"r15", Register(8, "r15", "r15d", "r15w", "r15b", "")}
    };
    for (const auto& regRecord : registerMap)
    {
        auto qwVerName = regRecord.second.qwordVersionName;
        auto dwVerName = regRecord.second.dwordVersionName;
        auto wVerName = regRecord.second.wordVersionName;
        auto bVerName = regRecord.second.byteVersionName;
        auto hbVerName = regRecord.second.highByteVersionName;

        registerMap[regRecord.second.dwordVersionName] =
                Register(4, qwVerName, dwVerName, wVerName, bVerName, hbVerName);

        registerMap[regRecord.second.wordVersionName] =
                Register(2, qwVerName, dwVerName, wVerName, bVerName, hbVerName);

        registerMap[regRecord.second.byteVersionName] =
                Register(1, qwVerName, dwVerName, wVerName, bVerName, hbVerName);

        registerMap[regRecord.second.highByteVersionName] =
                Register(1, qwVerName, dwVerName, wVerName, bVerName, hbVerName);
    }
}

std::string Analyser::getParentRegisterName(const std::string& regName)
{
    if (registerMap.find(regName) != registerMap.end()) {
        return registerMap[regName].qwordVersionName;
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
                std::string parentRegName = getParentRegisterName(instr.arguments[1]);
                if (!registerMap[parentRegName].wasChanged) {
                    std::string argName = std::string("arg") + std::to_string(parameterCounter);
                    std::string type = sizeToTypeMap[registerMap[instr.arguments[1]].byteSize];
                    function.parameters.push_back(Variable{type, argName});
                    function.aliasMap[parentRegName] = argName;
                    parameterCounter++;
                }
            }
        }
    }
}
