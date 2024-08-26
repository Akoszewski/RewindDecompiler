#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <utility>

bool isHexNumberWithNoPrefix(const std::string& str);
bool isHexByteWithNoPrefix(const std::string& str);
bool isHexNumberWithPrefix(const std::string& str);
bool isDecNumber(const std::string& str);
bool isNumber(const std::string& str);
void fixHexArgumentPrefix(std::string& argument);

#endif
