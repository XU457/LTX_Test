#include "dataparser.h"

DataParser::DataParser() { }

std::vector<std::vector<std::string>> DataParser::getCSVContent() {

    // A better choice would be to use std::array here as i know the no. of columns but i am keeping it a vector if different csv are tested with it
    std::vector<std::vector<std::string>> csvContent;
    std::filesystem::path filePath = *fileName;

    std::ifstream readFile(filePath);
    if (readFile.is_open()) {

        std::string line;
        while(std::getline(readFile, line)) {

            auto getCommaSeparation = [&]() {

                std::vector<std::string> commaSeparated;
                std::string colData;

                for (auto &chr : line) {

                    if (chr == ',') {
                        commaSeparated.push_back(colData);
                        colData = "";
                    }
                    if (chr == '"' ||  chr == ',' || chr == '\n') {
                        continue;
                    }
                    colData.push_back(chr);
                }

                // The last value
                commaSeparated.push_back(colData);

                return commaSeparated;
            };

            csvContent.push_back(getCommaSeparation());
        }

        readFile.close();

    } else {
        std::cout << "[ERROR]: Had some issue opening the file." << std::endl;
        return csvContent;
    }

    return csvContent;
}

DataParser::~DataParser() {

}
