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

std::vector<double> * FileProcessor::readMultivariate(std::string fileName, int lines, int variables, int * inputCols, int targetValCol) {
    
    std::string line;
    std::ifstream file (fileName);
    std::string token;
    int tokenNo = 0;
    int lineNo = 0;
    
    std::vector<double> target;
    
    std::vector<double> * data;
    data = new std::vector<double>[lines+1];
    
    if (file.is_open()) {
        while ( getline (file,line) ) {
            std::vector<double> input;
            lineNo++;
            try{
                std::stringstream ss(line);
                tokenNo = 0;
                while(std::getline(ss, token, ',')) {
                    if (tokenNo == targetValCol) {
                        target.push_back(std::stod(token));
                    } else if (inputCols[tokenNo] == 1) {
                        input.push_back(std::stod(token));
                    }
                    tokenNo++;
                }
                data[lineNo-1] = input;
            } catch (std::exception& e) {
                std::vector<double> input (variables-1,0.0);
                data[lineNo-1] = input;
                target.push_back(0.0);
                std::cout<<std::endl<<"Error in line "<<lineNo<<": "<<e.what()<<std::endl;
            }    
            if (lineNo == lines) break;
        }
        file.close();
        data[lines] = target;
    }
    else std::cout << "Unable to open file '"<<fileName<<"'"; 
    return data;
    
}

int FileProcessor::write(std::string fileName) {
    out_file.open(fileName,std::ofstream::out | std::ofstream::app);
    return 0;
}

int FileProcessor::append(std::string line) {
    out_file<<"";
    return 0;
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
