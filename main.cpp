/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on April 8, 2018, 12:46 PM
 */

#include <cstdlib>
#include <vector>

#include "LSTMNet.h"
#include "Preprocessor.h"
#include "FileReader.h"

/*
 * 
 */
int main(int argc, char** argv) {

    
    std::vector<double> *tmp;
    tmp = new std::vector<double>();
    tmp->push_back(1);
    tmp->push_back(2);
    tmp->push_back(4);
    tmp->push_back(8);
    tmp->push_back(3);
    
    
    Preprocessor * preproc;
    preproc = new Preprocessor();
    *tmp =  preproc->process(*tmp);
    
    preproc->printVector(*tmp);
    
//    FileReader * reader = new FileReader();
//    
//    std::vector<double> output;
//    output = reader->read("datasets/hr.txt",1);
//    int dataSize = 40;
//    
//    std::vector<double> * input;
//    input = new std::vector<double>[dataSize];
//    std::vector<double> inputVec;
//    
//    int sec;
//    
//    for (int i = 0; i < dataSize; i++) {
//        inputVec.clear();
//        
//        inputVec.push_back(i/120);
////        std::cout<<i/120<<' ';
//        
//        inputVec.push_back((i/2)%60);
////        std::cout<<(i/2)%60<<' ';
//        
//        if (i%2 == 0) inputVec.push_back(0);
//        else inputVec.push_back(5);
////        std::cout<<i%2<<' '<<'\n';
//        
//        input[i] = inputVec;
//        
//    }
//    
//    
//    int neurons = 1;
//    int inputVecSize = 3;
//    int trainDataSize = dataSize;
//    int timeSteps = 20;
//    float learningRate = 0.000001;
//    
//    LSTMNet * lstm = new LSTMNet(neurons,inputVecSize);
//    lstm->train(input, output, trainDataSize, timeSteps, learningRate);
//  
//    std::vector<double> vec1;
//    input = new std::vector<double>[1];
//    
//    vec1.clear();
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(0);
//    input[0] = vec1;
//    
//    lstm->predict(input);
//    
//    vec1.clear();
//    vec1.push_back(0);
//    vec1.push_back(9);
//    vec1.push_back(5);
//    input[0] = vec1;
//    
//    lstm->predict(input);
//    
//    vec1.clear();
//    vec1.push_back(0);
//    vec1.push_back(10);
//    vec1.push_back(4);
//    input[0] = vec1;
//    
//    lstm->predict(input);
//    
//    vec1.clear();
//    vec1.push_back(1);
//    vec1.push_back(1);
//    vec1.push_back(1);
//    input[0] = vec1;
//    
//    lstm->predict(input);
    
    
    
    return 0;
}

