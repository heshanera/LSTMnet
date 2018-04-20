/* 
 * File:   Preprocessor.h
 * Author: heshan
 *
 * Created on April 20, 2018, 8:00 PM
 */

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <vector>

class Preprocessor {
public:
    Preprocessor();
    Preprocessor(const Preprocessor& orig);
    virtual ~Preprocessor();
    
    std::vector<double> process(std::vector<double> vec); 
    int printVector(std::vector<double> vec);
    
    
private:

};

#endif /* PREPROCESSOR_H */

