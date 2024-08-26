#include "Utils.hpp"

bool isHexNumber(const std::string& str)
{
    for (char c : str)
    {
        if (!std::isxdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isHexByte(const std::string& str)
{
    return str.size() == 2 && isHexNumber(str);
}

void fixHexArgumentPrefix(std::string& argument)
{
    if (isHexNumber(argument)) {
        argument = "0x" + argument;
    }
}
