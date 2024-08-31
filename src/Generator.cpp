#include "Generator.hpp"
#include "Parser.hpp"
#include "Analyser.hpp"
#include "Utils.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>

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

std::string Generator::generateFunctionDefinitionHead(const Function& function)
{
    std::stringstream stream;

    stream << function.type << " " <<  function.name << "(";
    bool isFirst = true;
    for (const auto& param : function.parameters)
    {
        if (isFirst) {
            stream << param.type << " " << param.name;
            isFirst = false;
        } else {
            stream << ", " << param.type << " " << param.name;
        }
    }
    stream << ")\n{\n";

    return stream.str();
}

std::string Generator::generateFunctionCall(const Function& function, std::vector<std::string> params)
{
    std::stringstream stream;

    std::reverse(params.begin(), params.end());

    stream << "\t" << function.name << "(";
    bool isFirst = true;
    for (const auto& param : params)
    {
        if (isFirst) {
            stream << param;
            isFirst = false;
        } else {
            stream << ", " << param;
        }
    }

    stream << ");" << std::endl;

    return stream.str();
}

std::string Generator::generateFunction(const Function& function)
{
    std::stringstream stream;

    stream << generateFunctionDefinitionHead(function);

    Analyser analyser;

    std::vector <std::string> nextCalledFunctionParameters;

    for (const auto& instruction : function.instructions)
    {
        if (analyser.isFromFunctionPrologue(instruction)) {
            continue;
        } else if (analyser.isFromFunctionEpilogueExceptRet(instruction)) {
            continue;
        } else if (instruction.operand == "endbr64") {
            continue;
        } else if (instruction.operand == "mov") {
            if (analyser.isParameterRegister(instruction.arguments[0]) && isNumber(instruction.arguments[1])) {
                nextCalledFunctionParameters.push_back(instruction.arguments[1]);
                std::string parentRegName = analyser.getParentRegisterName(instruction.arguments[0]);
                analyser.registerMap[parentRegName].status = RegStatus::IsKnownNumber;
                analyser.registerMap[parentRegName].value = std::stoi(instruction.arguments[1]);
            }
            else if (instruction.arguments[0] == "eax" && isNumber(instruction.arguments[1])) {
                analyser.registerMap["rax"].status = RegStatus::IsKnownNumber;
                analyser.registerMap["rax"].value = std::stoi(instruction.arguments[1]);
            } else {
                stream << generateInlineAsm(instruction);
            }
        } else if (instruction.operand == "ret") {
            if (analyser.registerMap["rax"].status == RegStatus::IsKnownNumber) {
                stream << "\treturn " << analyser.registerMap["rax"].value << ";" << std::endl;
            }
        } else if (instruction.operand == "call" && isHexNumberWithPrefix(instruction.arguments[0])) {
            std::size_t pos = 2;
            std::optional<Function> functionOptional =
                    analyser.findFunctionWithAddress(std::stoi(instruction.arguments[0], &pos, 16));
            if (functionOptional.has_value()) {
                stream << generateFunctionCall(functionOptional.value(), nextCalledFunctionParameters);
                nextCalledFunctionParameters.clear();
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
