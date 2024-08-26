#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>

class FileManager
{
public:
    std::string readFile(std::string filePath);
    void writeToFile(std::string filePath, std::string content);
};

#endif
