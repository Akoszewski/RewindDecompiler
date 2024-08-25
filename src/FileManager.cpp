#include "FileManager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

std::string FileManager::readFile(std::string filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Couldn't open file for reading: " << filePath << std::endl;
        return "";
    }
    std::stringstream bufferstream;
    bufferstream << file.rdbuf();
    file.close();
    return bufferstream.str();
}

void FileManager::writeToFile(std::string filePath, std::string content)
{
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Couldn't open file for writing: " << filePath << std::endl;
        return;
    }
    file << content;
    file.close();
}
