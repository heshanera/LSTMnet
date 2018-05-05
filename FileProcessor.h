/* 
 * File:   FileProcessor.h
 * Author: heshan
 *
 * Created on April 14, 2018, 7:45 PM
 */

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>

class FileProcessor {
public:
    FileProcessor();
    FileProcessor(const FileProcessor& orig);
    virtual ~FileProcessor();
    
    std::vector<double> read(std::string fileName, int valuesPerLine);
    std::vector<double> * readMultivariate(std::string fileName, int lines, int variables, int targetValCol);
    
    int write(std::string fileName);
    int append(std::string line);
    int writeUniVariate(std::string fileName, std::string outFileName, int valuesPerLine, int columnIndx);
    
private:
    std::ofstream out_file;

};

#endif /* FILEPROCESSOR_H */

