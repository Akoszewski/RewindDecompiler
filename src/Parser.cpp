#include "Parser.hpp"
#include "Utils.hpp"
#include "Analyser.hpp"

#include <sstream>
#include <iostream>

Parser& Parser::getInstance()
{
    static Parser instance;
    return instance;
}

void Parser::Tokenize(const std::string& asmCode)
{
    std::istringstream stream(asmCode);
    std::string line;
    
    while (std::getline(stream, line))
    {
        std::istringstream lineStream(line);
        std::string token;
        while (lineStream >> token)
        {
            tokens.push_back(token);
        }
        tokens.push_back("\n");
    }
}

std::string Parser::generateFunctionName(int startTokenNumber)
{
    return generateFunctionNameFromUnstripped(startTokenNumber);
}

std::string Parser::generateFunctionNameFromUnstripped(int startTokenNumber)
{
    return tokens[startTokenNumber].substr(1, tokens[startTokenNumber].size() - 3);
}

bool Parser::detectDllTrampoline(int startTokenNumber)
{
    return tokens[startTokenNumber].find('@') != std::string::npos;
}

void clearInstructionInitializationTempData(InstructionInitializationTempData& initTempData)
{
    initTempData.isAddressInitialized = false;
    initTempData.isHexBytesPassed = false;
    initTempData.isOperandRead = false;
    initTempData.argumentsStr.clear();
}

std::vector<std::string> parseInstructionArgumentString(std::string argumentString)
{
    std::vector<std::string> arguments;
    std::string argument;
    for (int i = 0; i < argumentString.size(); i++)
    {
        if (argumentString[i] != ',') {
            argument += argumentString[i];
        } else {
            fixHexArgumentPrefix(argument);
            arguments.push_back(argument);
            argument.clear();
        }
    }
    if (!argument.empty()) {
        fixHexArgumentPrefix(argument);
        arguments.push_back(argument);
    }
    return arguments;
}

void finalizeInstructionInitialization(Instruction& instruction, InstructionInitializationTempData& initTempData)
{
    instruction.arguments = parseInstructionArgumentString(initTempData.argumentsStr);
    clearInstructionInitializationTempData(initTempData);
}

void fixDllFunctionName(Function& function)
{
    std::size_t pos = function.name.find('@');
    if (pos != std::string::npos) {
        function.name.erase(pos);
    }
}

Function Parser::parseFunction(std::pair<int, int> functionBoundary)
{
    Function function;
    function.name = generateFunctionName(functionBoundary.first);

    function.isDllTrampoline = detectDllTrampoline(functionBoundary.first);
    if (function.isDllTrampoline) {
        fixDllFunctionName(function);
        std::size_t pos = 0;
        function.address = std::stoi(tokens[functionBoundary.first + 2], &pos, 16);
        return function;
    }

    Instruction instruction;
    InstructionInitializationTempData initTempData;
    std::vector<std::string> arguments;

    for (int i = functionBoundary.first + 1; i <= functionBoundary.second; i++)
    {
        if (tokens[i] == "\n") {
            finalizeInstructionInitialization(instruction, initTempData);
            if (!instruction.operand.empty()) {
                function.instructions.emplace_back(instruction);
            }
            instruction.comment.clear();
            continue;
        }

        if (tokens[i] == "#" || tokens[i][0] == '<') {
            while (tokens[i] != "\n")
            {
                instruction.comment.push_back(tokens[i]);
                i++;
            }
            finalizeInstructionInitialization(instruction, initTempData);
            if (!instruction.operand.empty()) {
                function.instructions.emplace_back(instruction);
            }
            instruction.comment.clear();
            continue;
        }

        if (!initTempData.isAddressInitialized) {
            std::size_t pos = tokens[i].size() - 1;
            instruction.address = std::stoi(tokens[i], &pos, 16);
            initTempData.isAddressInitialized = true;
            continue;
        }

        if (!initTempData.isHexBytesPassed && isHexByteWithNoPrefix(tokens[i])) {
            continue;
        }
        initTempData.isHexBytesPassed = true;

        if (!initTempData.isOperandRead) {
            instruction.operand = tokens[i];
            initTempData.isOperandRead = true;
            continue;
        }

        if (!initTempData.argumentsStr.empty()) {
            initTempData.argumentsStr.append(" ");
        }
        initTempData.argumentsStr.append(tokens[i]);
    }
    if (!function.instructions.empty()) {
        function.address = function.instructions[0].address;
    }

    Analyser analyser;
    analyser.initFunctionParameters(function);
    function.type = "int"; // TODO: get from analysis

    return function;
}

std::optional<Function> Parser::findFunctionWithName(const std::string& name)
{
    std::optional<Function> functionOptional;
    for (const auto& f : functions)
    {
        if (f.name == name) {
            return std::optional(f);
        }
    }
    return functionOptional;
}

void Parser::parseAllFunctions(std::vector<std::pair<int, int>> functionBoundaries)
{
    for (const auto& boundary : functionBoundaries)
    {
        Function function = parseFunction(boundary);
        if (function.isDllTrampoline) {
            functions.push_back(function);
        } else {
            if (!function.instructions.empty()) {
                functions.push_back(function);
            }
        }
    }
}

std::vector<std::pair<int, int>> Parser::findFunctionBoundaries()
{
    return findFunctionBoundariesInNonStripped();
}


std::vector<std::pair<int, int>> Parser::findFunctionBoundariesInNonStripped()
{
    std::vector<std::pair<int, int>> functionBoundaries;

    int startTokenNumber = -1;
    int endTokenNumber = -1;
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i][0] == '<' && tokens[i][tokens[i].size() - 2] == '>' && tokens[i][tokens[i].size() - 1] == ':') {
            if (tokens[i][1] != '_' && tokens[i].find("@plt-") == std::string::npos) {
                startTokenNumber = i;
            }
        }
        if (startTokenNumber != -1) {
            if (tokens[i][0] == '\n' && i + 1 < tokens.size() && tokens[i+1][0] == '\n') {
                endTokenNumber = i;
                functionBoundaries.emplace_back(startTokenNumber, endTokenNumber);
                startTokenNumber = -1;
                endTokenNumber = -1;
            }
        }
    }

    if (functionBoundaries.empty()) {
        std::cout << "No functions found. The binary was probably stripped. ";
        std::cout << "Stripped binaries will hopefully be supported in the future" << std::endl;
    }
    return functionBoundaries;
}
