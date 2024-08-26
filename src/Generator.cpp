#include "Generator.hpp"
#include "Parser.hpp"

#include <iostream>
#include <sstream>

std::string Generator::generateCodeFromAsm(std::string objdumpAsmCode)
{
    Parser parser(objdumpAsmCode);
    std::vector<std::pair<int, int>> functionBoundaries = parser.findFunctionBoundaries();
    parser.parseAllFunctions(functionBoundaries);
    
    std::stringstream stream;
    for (const auto& function : parser.functions)
    {
        std::string type = "int"; // TODO: get from parsing
        std::string typeStr = type.empty() ? "" : type + " ";
        stream << typeStr <<  function.name << "()" << std::endl << "{" << std::endl;
        for (const auto& instruction : function.instructions)
        {
            stream << "\tasm(\"" << instruction.operand;
            for (int i = 0; i < instruction.arguments.size(); i++)
            {
                if (i > 0) {
                    stream << ",";
                }
                stream << " " << std::dec << instruction.arguments[i];
            }
            stream << "\");" << std::endl;
        }
        stream << "}" << std::endl << std::endl;
    }
    return stream.str();
}

std::string Generator::generateInstruction()
{
    return "";
}

std::string Generator::generateFunction()
{
    return "";
}
