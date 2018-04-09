/* 
 * File:   MemoryCell.cpp
 * Author: heshan
 * 
 * Created on April 8, 2018, 2:11 PM
 */

#include "LSTMNet.h"

LSTMNet::LSTMNet() {
}

LSTMNet::LSTMNet(const LSTMNet& orig) {
}

LSTMNet::~LSTMNet() {
}

double LSTMNet::forgetGate() {
    
}

int LSTMNet::forward() {
    initWeights();
    
}

int LSTMNet::initWeights() {
    
    int vectorSize = neurons + inputVectDim;
    
    Wf = new double*[vectorSize]; 
    for(int i = 0; i < vectorSize; i++) {
        Wf[i] = new double[neurons];
        for(int j = 0; j < neurons; j++) {
            double w = (double)rand() / RAND_MAX;
            Wf[i][j] = -1 + w * 2; // Min + w * (Max - Min);
            std::cout<<(-1 + w * 2)<<" ";
        }
        std::cout<<"\n";
    }   
    
    Wi = new double*[vectorSize]; 
    for(int i = 0; i < vectorSize; i++) {
        Wi[i] = new double[neurons];
        for(int j = 0; j < neurons; j++) {
            double w = (double)rand() / RAND_MAX;
            Wi[i][j] = -1 + w * 2; // Min + w * (Max - Min);
            std::cout<<(-1 + w * 2)<<" ";
        }
        std::cout<<"\n";
    }  
    
    Wc = new double*[vectorSize]; 
    for(int i = 0; i < vectorSize; i++) {
        Wc[i] = new double[neurons];
        for(int j = 0; j < neurons; j++) {
            double w = (double)rand() / RAND_MAX;
            Wc[i][j] = -1 + w * 2; // Min + w * (Max - Min);
            std::cout<<(-1 + w * 2)<<" ";
        }
        std::cout<<"\n";
    }  
    
    Wo = new double*[vectorSize]; 
    for(int i = 0; i < vectorSize; i++) {
        Wo[i] = new double[neurons];
        for(int j = 0; j < neurons; j++) {
            double w = (double)rand() / RAND_MAX;
            Wo[i][j] = -1 + w * 2; // Min + w * (Max - Min);
            std::cout<<(-1 + w * 2)<<" ";
        }
        std::cout<<"\n";
    }  
    
    Wy = new double*[neurons]; 
    for(int i = 0; i < neurons; i++) {
        Wy[i] = new double[inputVectDim];
        for(int j = 0; j < inputVectDim; j++) {
            double w = (double)rand() / RAND_MAX;
            Wy[i][j] = -1 + w * 2; // Min + w * (Max - Min);
            std::cout<<(-1 + w * 2)<<" ";
        }
        std::cout<<"\n";
    } 
    
    biasArr = new double*[4];
    for(int i = 0; i < 4; i++) {
        biasArr[i] = new double[neurons];
        for(int j = 0; j < neurons; j++) {
            biasArr[i][j] = 0;
            std::cout<<0<<" ";
        }
        std::cout<<"\n";
    }
    
    by = new double[inputVectDim];
    for(int j = 0; j < inputVectDim; j++) {
        by[j] = 0;
        std::cout<<0<<" ";
    }
    
}

double LSTMNet::sigmoid(double x) {
    return 1/(1 + std::pow (std::exp(1.0), -x));
}

int LSTMNet::test() {
    
    neurons = 6;
    inputVectDim = 4;
    
    initWeights();
}