#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

class DataParser {
    std::shared_ptr<std::string> fileName;
public:
    DataParser();
    DataParser(std::shared_ptr<std::string> filename) : fileName(filename) {}
    ~DataParser();

    std::vector<std::vector<std::string>> getCSVContent();
};

#endif // DATAPARSER_H
