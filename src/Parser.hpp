#ifndef PARSER_HPP
#define PARSER_HPP

#include "Function.hpp"

#include <utility>
#include <optional>

class Parser
{
public:
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    static Parser& getInstance();
    void Tokenize(const std::string& asmCode);
    std::vector<std::pair<int, int>> findFunctionBoundaries();
    Function parseFunction(std::pair<int, int> functionBoundary);
    void parseAllFunctions(std::vector<std::pair<int, int>> functionBoundaries);
    std::optional<Function> findFunctionWithName(const std::string& name);
    std::vector<Function> functions;
private:
    Parser();
    std::vector<std::pair<int, int>> findFunctionBoundariesInNonStripped();
    std::string generateFunctionName(int startTokenNumber);
    std::string generateFunctionNameFromUnstripped(int startTokenNumber);
    bool detectDllTrampoline(int startTokenNumber);
    std::vector<std::string> tokens;
};

#endif
