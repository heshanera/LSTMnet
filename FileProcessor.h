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
    
    int write(std::string fileName);
    int append(std::string line);
private:
    std::ofstream out_file;

};

#endif /* FILEPROCESSOR_H */

