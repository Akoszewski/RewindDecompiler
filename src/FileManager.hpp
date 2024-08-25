#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

class FileManager
{
public:
    std::string readFile(std::string filePath);
    void writeToFile(std::string filePath, std::string content);
};

#endif
