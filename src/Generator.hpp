#ifndef GENERATOR_HPP
#define GENEATOR_HPP

#include <string>

class Generator
{
public:
    std::string generateCodeFromAsm(std::string objdumpAsmCode);
private:
    std::string generateInstruction();
    std::string generateFunction();
};

#endif
