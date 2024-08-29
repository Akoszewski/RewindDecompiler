#ifndef GENERATOR_HPP
#define GENEATOR_HPP

#include "Function.hpp"

#include <string>

class Generator
{
public:
    std::string generateCodeFromAsm(const std::string& objdumpAsmCode);
private:
    std::string generateInlineAsm(const Instruction& instruction);
    std::string generateFunction(const Function& function);
    std::string generateFunctionDefinitionHead(const Function& function);
};

#endif
