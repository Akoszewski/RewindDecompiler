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

    stream << function.name << "(";
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

std::string Generator::generateNewVariableName(VariableKind kind)
{
    static int localVarCounter = 0;
    static int retVarCounter = 0;
    std::string result;

    switch (kind)
    {
        case VariableKind::LOCAL:
            localVarCounter++;
            result = std::string("var") + std::to_string(localVarCounter);
        break;
        case VariableKind::RETURN:
            retVarCounter++;
            result = std::string("ret") + std::to_string(retVarCounter);
        break;
    }
    return result;
}

char getSymbol(const std::string& operand)
{
    if (operand == "mov" || operand == "movsx" || operand == "movzx" || operand == "lea") {
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

void replaceNewlineWithLiteral(std::string& input)
{
    const std::string literalNewline = "\\n";
    size_t pos = 0;

    while ((pos = input.find('\n', pos)) != std::string::npos)
    {
        input.replace(pos, 1, literalNewline);
        pos += literalNewline.length();
    }
}

std::string getCStringFromAddress(const long long& address)
{
    const int rodataAddress = 2000;
    std::vector<unsigned char>& rodataBytes = Parser::getInstance().rodataBytes;
    std::string extractedString;

    std::cout << "address: " << address << std::endl;
    for (int i = address - rodataAddress;; i++)
    {
        if (rodataBytes[i] == 0)
        {
            break;
        }
        std::cout << "RodataByte: " << rodataBytes[i] << std::endl;
        extractedString += rodataBytes[i];
    }
    replaceNewlineWithLiteral(extractedString);

    std::string res = "\"" + extractedString + "\"";
    std::cout << "The string from rodata: " << res << " " << "Disk address: " << address << std::endl;
    return res;
}

std::string Generator::generateFunction(Function& function)
{
    std::stringstream stream;

    stream << generateFunctionDefinitionHead(function);

    Analyser analyser;

    std::vector <std::string> nextCalledFunctionParameters;

    for (const auto& instruction : function.instructions)
    {
        std::string instructionType = "int";
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
            else if (analyser.getParentRegisterName(instruction.arguments[0]) == "rax" && isNumber(instruction.arguments[1])) {
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
                if (instruction.operand == "lea")
                {
                    std::cout << "instruction.comment[1]: " << instruction.comment[1] << std::endl;
                    rvalue = getCStringFromAddress(std::stoll(instruction.comment[1]));
                }
                else
                {
                    if (!isNumber(argumentContentRight)) {
                        if (function.aliasMap.find(argumentContentRight) == function.aliasMap.end()) {
                            std::cout << "Error: Could not find alias for: argumentContentRight = " << argumentContentRight << std::endl;
                        }
                        rvalue = function.aliasMap[argumentContentRight];
                    } else {
                        rvalue = argumentContentRight;
                    }
                }
                std::string typeDeclaration = shouldDeclare ? instructionType + std::string(" ") : "";

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
            } else {
                if (function.aliasMap.find("rax") != function.aliasMap.end()) {
                    stream << "\treturn " << function.aliasMap["rax"] << ";" << std::endl;
                }
            }
        } else if (instruction.operand == "call" && isHexNumberWithPrefix(instruction.arguments[0])) {
            std::size_t pos = 2;
            std::optional<Function> functionOptional =
                    analyser.findFunctionWithAddress(std::stoi(instruction.arguments[0], &pos, 16));
            if (functionOptional.has_value()) {
                if (functionOptional.value().type == "void") {
                    stream << "\t" << generateFunctionCall(functionOptional.value(), nextCalledFunctionParameters);
                } else {
                    std::string retVarName = generateNewVariableName(VariableKind::RETURN);
                    stream << "\t" << functionOptional.value().type << " " << retVarName << " = " << 
                        generateFunctionCall(functionOptional.value(), nextCalledFunctionParameters);
                    function.aliasMap["rax"] = retVarName;
                    analyser.registerMap["rax"].status = RegStatus::IsEqualToOtherUnit;
                    analyser.registerMap["rax"].value = 0;
                }
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
    Parser::getInstance().parseRodata();

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
