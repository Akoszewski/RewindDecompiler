#ifndef GENERATOR_HPP
#define GENEATOR_HPP

#include "Function.hpp"

#include <string>

enum class VariableKind
{
    LOCAL,
    RETURN
};

class Generator
{
public:
    std::string generateCodeFromAsm(const std::string& objdumpAsmCode);
private:
    std::string generateInlineAsm(const Instruction& instruction);
    std::string generateFunction(Function& function);
    std::string generateFunctionDefinitionHead(const Function& function);
    std::string generateFunctionCall(const Function& function, std::vector<std::string> nextCalledFunParams);
    std::string generateNewVariableName(VariableKind kind = VariableKind::LOCAL);
};

#endif
