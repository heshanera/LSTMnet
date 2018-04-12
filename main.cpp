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
    int trainDataSize = 2;
    int timeSteps = 2;
    float learningRate = 0.1;
    
    LSTMNet * lstm = new LSTMNet(neurons,inputVecSize);
    
    std::vector<double> * input;
    input = new std::vector<double>[2];
    
    std::vector<double> vec1;
    vec1.push_back(0.1);
    vec1.push_back(0.3);
    vec1.push_back(0.8);
    vec1.push_back(1.1);
    vec1.push_back(2.3);
    
    std::vector<double> vec2;
    vec2.push_back(2.1);
    vec2.push_back(0.5);
    vec2.push_back(1.5);
    vec2.push_back(0.7);
    vec2.push_back(3.4);
    
    input[0] = vec1;
    input[1] = vec2;
    
    std::vector<double> output;
    output.push_back(1);
    output.push_back(2);
    
    lstm->train(input, output, trainDataSize, timeSteps, learningRate);
    
    return 0;
}

