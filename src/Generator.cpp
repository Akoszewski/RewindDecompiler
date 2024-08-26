#include "Generator.hpp"
#include "Parser.hpp"
#include "Analyser.hpp"

#include <iostream>
#include <sstream>

std::string Generator::generateInlineAsm(const Instruction& instruction)
{
    std::stringstream stream;
    stream << "\tasm(\"" << instruction.operand;
    for (int i = 0; i < instruction.arguments.size(); i++)
    {
        if (i > 0) {
            stream << ",";
        }
        stream << " " << instruction.arguments[i];
    }
    stream << "\");" << std::endl;
    return stream.str();
}

std::string Generator::generateFunction(const Function& function)
{
    std::stringstream stream;
    std::string type = "int"; // TODO: get from parsing
    std::string typeStr = type.empty() ? "" : type + " ";
    stream << typeStr <<  function.name << "()" << std::endl << "{" << std::endl;

    Analyser analyser;
    for (const auto& instruction : function.instructions)
    {
        if (analyser.isFromFunctionPrologue(instruction)) {
            continue;
        } else if (analyser.isFromFunctionEpilogue(instruction)) {
            continue;
        } else if (instruction.operand == "endbr64") {
            continue;
        }
        stream << generateInlineAsm(instruction);
    }
    stream << "}" << std::endl << std::endl;
    return stream.str();
}

std::string Generator::generateCodeFromAsm(const std::string& objdumpAsmCode)
{
    Parser parser(objdumpAsmCode);
    std::vector<std::pair<int, int>> functionBoundaries = parser.findFunctionBoundaries();
    parser.parseAllFunctions(functionBoundaries);
    
    std::stringstream stream;
    for (const auto& function : parser.functions)
    {
        stream << generateFunction(function);
    }
    return stream.str();
}
