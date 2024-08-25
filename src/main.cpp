#include "FileManager.hpp"
#include "Generator.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    FileManager fileManager;
    std::string asmCode = fileManager.readFile(std::string(argv[1]));
    Generator generator;
    std::string decompiledCode = generator.generateCodeFromAsm(asmCode);
    fileManager.writeToFile("output.c", decompiledCode);
    return 0;
}
