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
    
    /**
     * 
     * @param fileName name of the input file
     * @param valuesPerLine number of values in line
     * @return vector of values
     */
    std::vector<double> read(std::string fileName, int valuesPerLine);
    /**
     * Read a text file containing comma separated values.
     * 
     * @param fileName file name of the multivariate data series
     * @param lines no of lines that should be read
     * @param variables variable in the file
     * @param inputCols index of the variable in a line that should used to create the vector
     * @param targetValCol index of the target value column
     * @return an array of vectors
     * 
     * each vector contain variables in one row
     * last array vector is the target vector 
     */
    std::vector<double> * readMultivariate(std::string fileName, int lines, int variables, int * inputCols, int targetValCol);
    /**
     * 
     * @param fileName
     * @return 
     */
    int write(std::string fileName);
    /**
     * 
     * @param line
     * @return 
     */
    int append(std::string line);
    /**
     * 
     * @param fileName: input filename
     * @param outFileName: output file name
     * @param valuesPerLine: values in a line in the input file
     * @param columnIndx: variable written to the output file
     * @return 0
     */
    int writeUniVariate(std::string fileName, std::string outFileName, int valuesPerLine, int columnIndx);
    
private:
    std::ofstream out_file;

};

#endif /* FILEPROCESSOR_H */

