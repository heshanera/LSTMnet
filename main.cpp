/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on April 8, 2018, 12:46 PM
 */

#include <cstdlib>

#include "LSTMNet.h"

/*
 * 
 */
int main(int argc, char** argv) {

    int neurons = 1;
    int inputVecSize = 5;
    int trainDataSize = 100;
    int timeSteps = 5;
    float learningRate = 0.01;
    
    LSTMNet * lstm = new LSTMNet(neurons,inputVecSize);
    
    std::vector<double> * input;
    input = new std::vector<double>[100];
    
    std::vector<double> inputVec;
    for (int i = 0; i < 100; i+=5) {
        
        inputVec.clear();
        for (int j = 0; j < 5; j++ ){
            inputVec.push_back(0.1);
        }
        input[i] = inputVec;
        
        inputVec.clear();
        for (int j = 0; j < 5; j++ ){
            inputVec.push_back(0.2);
        }
        input[i+1] = inputVec;
        
        inputVec.clear();
        for (int j = 0; j < 5; j++ ){
            inputVec.push_back(0.3);
        }
        input[i+2] = inputVec;
        
        inputVec.clear();
        for (int j = 0; j < 5; j++ ){
            inputVec.push_back(0.2);
        }
        input[i+3] = inputVec;
        
        inputVec.clear();
        for (int j = 0; j < 5; j++ ){
            inputVec.push_back(0.1);
        }
        input[i+4] = inputVec;
        
    }
    
    std::vector<double> output;
    for (int i = 0; i < 50; i+=5) {
        
        output.push_back(1);
        output.push_back(2);
        output.push_back(3);
        output.push_back(2);
        output.push_back(1);
        
    }
    
    lstm->train(input, output, trainDataSize, timeSteps, learningRate);
    
    
    std::vector<double> vec1;
    input = new std::vector<double>[1];
    vec1.clear();
    vec1.push_back(0.1);
    vec1.push_back(0.1);
    vec1.push_back(0.1);
    vec1.push_back(0.1);
    vec1.push_back(0.1);
    input[0] = vec1;
    
    lstm->predict(input);
    
    vec1.clear();
    vec1.push_back(0.2);
    vec1.push_back(0.2);
    vec1.push_back(0.2);
    vec1.push_back(0.2);
    vec1.push_back(0.2);
    input[0] = vec1;
    
    lstm->predict(input);
    
    vec1.clear();
    vec1.push_back(0.3);
    vec1.push_back(0.3);
    vec1.push_back(0.3);
    vec1.push_back(0.3);
    vec1.push_back(0.3);
    input[0] = vec1;
    
    lstm->predict(input);
    
    return 0;
}

