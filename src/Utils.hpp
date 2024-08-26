#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

bool isHexNumber(const std::string& str);
bool isHexByte(const std::string& str);
void fixHexArgumentPrefix(std::string& argument);

#endif
