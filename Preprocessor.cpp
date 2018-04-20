/* 
 * File:   Preprocessor.cpp
 * Author: heshan
 * 
 * Created on April 20, 2018, 8:00 PM
 */

#include "Preprocessor.h"

#include <cmath>
#include <iostream>

Preprocessor::Preprocessor() { }

Preprocessor::Preprocessor(const Preprocessor& orig) { }

Preprocessor::~Preprocessor() { }

std::vector<double> Preprocessor::process(std::vector<double> vec) {

    std::cout<<"processing...\n";
    
    double magnitude = 0.0;
    for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
        magnitude += std::pow(*it,2);
    }
    magnitude = std::pow(magnitude,0.5);
    
    for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
        *it /= magnitude;
    }
    
    return vec;
    
}

int Preprocessor::printVector(std::vector<double> vec){
    
    for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it<<" ";
    }
    std::cout<<std::endl;
}
