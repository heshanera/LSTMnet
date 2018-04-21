/* 
 * File:   FileProcessor.cpp
 * Author: heshan
 * 
 * Created on April 14, 2018, 7:45 PM
 */

#include <vector>
#include <exception>

#include "FileProcessor.h"

FileProcessor::FileProcessor() { }

FileProcessor::FileProcessor(const FileProcessor& orig) { }

FileProcessor::~FileProcessor() { }

std::vector<double> FileProcessor::read(std::string fileName, int valuesPerLine) {
    
    std::vector<double> values;
    std::string line;
    std::ifstream file (fileName);
    int lineNo = 0;
    if (file.is_open()) {
        while ( getline (file,line) ) {
//            std::cout << line << '\n';
            lineNo++;
            try{
                values.push_back(std::stod(line));
            } catch (std::exception& e) {
                std::cout<<std::endl<<"Error in line "<<lineNo<<": "<<e.what()<<std::endl;
            }    
        }
        file.close();
    }
    else std::cout << "Unable to open file '"<<fileName<<"'"; 
    return values;
    
}

int FileProcessor::write(std::string fileName) {
    out_file.open(fileName,std::ofstream::out | std::ofstream::app);
}

int FileProcessor::append(std::string line) {
    out_file<<"";
}
