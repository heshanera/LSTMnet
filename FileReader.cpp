/* 
 * File:   FileReader.cpp
 * Author: heshan
 * 
 * Created on April 14, 2018, 7:45 PM
 */

#include <vector>

#include "FileReader.h"

FileReader::FileReader() { }

FileReader::FileReader(const FileReader& orig) { }

FileReader::~FileReader() { }

std::vector<double> FileReader::read(std::string fileName, int valuesPerLine) {
    
    std::vector<double> values;
    std::string line;
    std::ifstream file (fileName);
    if (file.is_open()) {
        while ( getline (file,line) ) {
//            std::cout << line << '\n';
            values.push_back(std::stod(line));
        }
        file.close();
    }
    else std::cout << "Unable to open file '"<<fileName<<"'"; 
    return values;
    
}

