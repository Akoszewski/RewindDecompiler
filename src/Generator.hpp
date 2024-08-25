#ifndef GENERATOR_H
#define GENEATOR_H

#include  <string>

class Generator
{
public:
    std::string generateCodeFromAsm(std::string objdumpAsmCode);
private:
    std::string generateInstruction();
    std::string generateFunction();
};

#endif
