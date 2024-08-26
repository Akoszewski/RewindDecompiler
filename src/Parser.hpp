#ifndef PARSER_HPP
#define PARSER_HPP

#include "Function.hpp"

#include <utility>

class Parser
{
public:
    Parser(std::string asmCode);
    std::vector<std::pair<int, int>> findFunctionBoundaries();
    Function parseFunction(std::pair<int, int> functionBoundary);
    void parseAllFunctions(std::vector<std::pair<int, int>> functionBoundaries);
    std::vector<Function> functions;
private:
    std::vector<std::string> tokens;
    std::vector<std::pair<int, int>> findFunctionBoundariesInNonStripped();
    std::string generateFunctionName(int startTokenNumber);
    std::string generateFunctionNameFromUnstripped(int startTokenNumber);
};

#endif
