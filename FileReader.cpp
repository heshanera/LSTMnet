/* 
 * File:   FileReader.cpp
 * Author: heshan
 * 
 * Created on April 14, 2018, 7:45 PM
 */

#include "FileReader.h"

FileReader::FileReader() { }

FileReader::FileReader(const FileReader& orig) { }

FileReader::~FileReader() { }

int FileReader::read(std::string fileName, int valuesPerLine) {
    
    std::string line;
    std::ifstream file (fileName);
    if (file.is_open()) {
        while ( getline (file,line) ) {
            std::cout << line << '\n';
        }
        file.close();
    }
    else std::cout << "Unable to open file '"<<fileName<<"'"; 
    return 0;
    
}

