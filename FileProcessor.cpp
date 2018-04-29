/* 
 * File:   FileProcessor.cpp
 * Author: heshan
 * 
 * Created on April 14, 2018, 7:45 PM
 */

#include <vector>
#include <exception>
#include <sstream>

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
        if (valuesPerLine == 1)  {
            while ( getline (file,line) ) {
                lineNo++;
                try{
                    values.push_back(std::stod(line));
                } catch (std::exception& e) {
                    std::cout<<std::endl<<"Error in line "<<lineNo<<": "<<e.what()<<std::endl;
                }    
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

int FileProcessor::writeUniVariate(std::string fileName, std::string outFileName, int valuesPerLine, int columnIndx) {
    
    std::string line;
    std::ifstream file (fileName);
    std::string token;
    int tokenNo = 0;
    int lineNo = 0;
    
    std::ofstream out_file;
    out_file.open(outFileName,std::ofstream::out | std::ofstream::trunc);
    
    if (file.is_open()) {
        if (valuesPerLine > 1) {
            while ( getline (file,line) ) {
                lineNo++;
                try{
                    std::stringstream ss(line);
                    tokenNo = 0;
                    while(std::getline(ss, token, ',')) {
                        if (tokenNo == columnIndx) {
                            out_file<<token<<"\n";
                        }
                        tokenNo++;
                    }
                } catch (std::exception& e) {
                    std::cout<<std::endl<<"Error in line "<<lineNo<<": "<<e.what()<<std::endl;
                }    
            }
        } 
        file.close();
    }
    else std::cout << "Unable to open file '"<<fileName<<"'"; 
    return 0;
    
}
