/* 
 * File:   Preprocessor.h
 * Author: heshan
 *
 * Created on April 20, 2018, 8:00 PM
 */

#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <vector>

class DataProcessor {
public:
    DataProcessor();
    DataProcessor(const DataProcessor& orig);
    virtual ~DataProcessor();
    
    /**
     * normalize the given vector
     * @param vec vector
     * @param vecType vector type input or output
     * @return normalized vector
     */
    std::vector<double> process(std::vector<double> vec, int vecType); 
    /**
     * post process the given vector
     * @param vec vector
     * @return processed vector
     */
    std::vector<double> postprocess(std::vector<double> vec);
    /**
     * post process a given double
     * @param val
     * @return 
     */
    double postProcess(double val);
    
    /**
     * Print the given vector
     * @param vec vector
     * @return 
     */
    int printVector(std::vector<double> vec);
    
    double out_magnitude;
    
private:
    

};

#endif /* DATAPROCESSOR_H */

