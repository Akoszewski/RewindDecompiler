#include "Utils.hpp"

bool isDecNumber(const std::string& str)
{
    for (char c : str)
    {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isHexNumberWithNoPrefix(const std::string& str)
{
    for (char c : str)
    {
        if (!std::isxdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isHexByteWithNoPrefix(const std::string& str)
{
    return str.size() == 2 && isHexNumberWithNoPrefix(str);
}

void fixHexArgumentPrefix(std::string& argument)
{
    if (isHexNumberWithNoPrefix(argument)) {
        argument = "0x" + argument;
    }
}

bool isHexNumberWithPrefix(const std::string& str)
{
    return str.size() >= 2 && str.substr(0, 2) == "0x";
}

bool isNumber(const std::string& str)
{
    return isHexNumberWithPrefix(str) || isHexNumberWithNoPrefix(str) || isDecNumber(str);
}
