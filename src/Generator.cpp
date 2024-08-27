#include "Generator.hpp"
#include "Parser.hpp"
#include "Analyser.hpp"
#include "Utils.hpp"

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

std::string generateExternalFunctionDeclaration(const Function& function)
{
    std::stringstream stream;
    std::string type = "int"; // TODO: get from parsing
    stream << type << " " << function.name << "();\n\n";
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
        } else if (analyser.isFromFunctionEpilogueExceptRet(instruction)) {
            continue;
        } else if (instruction.operand == "endbr64") {
            continue;
        } else if (instruction.operand == "mov") {
            if (instruction.arguments[0] == "eax" && isNumber(instruction.arguments[1])) {
                analyser.rax.status = RegStatus::IsKnownNumber;
                analyser.rax.value = std::stoi(instruction.arguments[1]);
            } else {
                stream << generateInlineAsm(instruction);
            }
        } else if (instruction.operand == "ret") {
            if (analyser.rax.status == RegStatus::IsKnownNumber) {
                stream << "\treturn " << analyser.rax.value << ";" << std::endl;
            }
        } else if (instruction.operand == "call" && isHexNumberWithPrefix(instruction.arguments[0])) {
            std::size_t pos = 2;
            std::optional<Function> functionOptional =
                    analyser.findFunctionWithAddress(std::stoi(instruction.arguments[0], &pos, 16));
            if (functionOptional.has_value()) {
                stream << "\t" << functionOptional.value().name << "();" << std::endl;
            } else {
                stream << generateInlineAsm(instruction);
            }
        } else {
            stream << generateInlineAsm(instruction);
        }
    }
    stream << "}" << std::endl << std::endl;
    return stream.str();
}

std::string Generator::generateCodeFromAsm(const std::string& objdumpAsmCode)
{
    Parser::getInstance().Tokenize(objdumpAsmCode);
    std::vector<std::pair<int, int>> functionBoundaries = Parser::getInstance().findFunctionBoundaries();
    Parser::getInstance().parseAllFunctions(functionBoundaries);
    
    std::stringstream stream;
    for (const auto& function : Parser::getInstance().functions)
    {
        if (function.isDllTrampoline) {
            stream << generateExternalFunctionDeclaration(function);
        } else {
            stream << generateFunction(function);
        }
    }
    return stream.str();
}
