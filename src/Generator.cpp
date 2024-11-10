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

std::string Generator::generateNewVariableName()
{
    static int varCounter = 0;
    varCounter++;
    return std::string("var") + std::to_string(varCounter);
}

char getSymbol(const std::string& operand)
{
    if (operand == "mov" || operand == "movsx" || operand == "movzx") {
        return '=';
    } else if (operand == "add") {
        return '+';
    } else if (operand == "sub") {
        return '-';
    } else if (operand == "mul" || operand == "imul") {
        return '*';
    } else if (operand == "div" || operand == "idiv") {
        return '/';
    }
    return ' ';
}

std::string Generator::generateFunction(Function& function)
{
    std::stringstream stream;

    stream << generateFunctionDefinitionHead(function);

    Analyser analyser;

    std::vector <std::string> nextCalledFunctionParameters;

    for (const auto& instruction : function.instructions)
    {
        // std::cout << "Instruction: " << instruction.operand << " " << instruction.arguments.size() << std::endl;
        if (analyser.isFromFunctionPrologue(instruction)) {
            continue;
        } else if (analyser.isFromFunctionEpilogueExceptRet(instruction)) {
            continue;
        } else if (instruction.operand == "endbr64") {
            continue;
        // } else if (instruction.operand == "mov" || instruction.operand == "movsx") {
        } else if (instruction.arguments.size() == 2) {
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
                bool shouldDeclare = false;
                std::string parentRegNameLeft = analyser.getParentRegisterName(instruction.arguments[0]);
                std::string parentRegNameRight = analyser.getParentRegisterName(instruction.arguments[1]);
                std::string argumentContentLeft = parentRegNameLeft.empty() ? instruction.arguments[0] : parentRegNameLeft;
                std::string argumentContentRight = parentRegNameRight.empty() ? instruction.arguments[1] : parentRegNameRight;
                if (function.aliasMap.find(argumentContentLeft) == function.aliasMap.end()) {
                    function.aliasMap[argumentContentLeft] = generateNewVariableName();
                    shouldDeclare = true;
                }
                std::string rvalue;
                if (!isNumber(argumentContentRight)) {
                    if (function.aliasMap.find(argumentContentRight) == function.aliasMap.end()) {
                        std::cout << "Error: Could not find alias for: argumentContentRight = " << argumentContentRight << std::endl;
                    }
                    rvalue = function.aliasMap[argumentContentRight];
                } else {
                    rvalue = argumentContentRight;
                }
                std::string typeDeclaration = shouldDeclare ? "int " : "";
                std::string lvalue = typeDeclaration + function.aliasMap[argumentContentLeft];
                if (getSymbol(instruction.operand) == '=') {
                    stream << "\t" << lvalue << " = " << rvalue << ";\n";
                } else {
                    stream << "\t" << lvalue << " = " << function.aliasMap[argumentContentLeft] << " " << getSymbol(instruction.operand) << " " << rvalue << ";\n";
                }
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
    for (auto& function : Parser::getInstance().functions)
    {
        if (function.isDllTrampoline) {
            stream << generateExternalFunctionDeclaration(function);
        } else {
            stream << generateFunction(function);
        }
    }
    return stream.str();
}
