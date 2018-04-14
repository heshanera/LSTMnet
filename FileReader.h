/* 
 * File:   FileReader.h
 * Author: heshan
 *
 * Created on April 14, 2018, 7:45 PM
 */

#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <string>

class FileReader {
public:
    FileReader();
    FileReader(const FileReader& orig);
    virtual ~FileReader();
    
    int read(std::string fileName, int valuesPerLine);
    
private:

};

#endif /* FILEREADER_H */

