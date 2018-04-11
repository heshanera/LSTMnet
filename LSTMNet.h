/* 
 * File:   MemoryCell.h
 * Author: heshan
 *
 * Created on April 8, 2018, 2:11 PM
 */

#ifndef LSTMNET_H
#define LSTMNET_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include <numeric>
#include <functional>


class LSTMNet {
public:
    LSTMNet();
    LSTMNet(const LSTMNet& orig);
    virtual ~LSTMNet();
    
    int forward(std::vector<double> Input);
    int backward();
    int train(int t);
    
    int test();
    
private:
    double sigmoid(double x);
    std::vector<double> sigmoid(std::vector<double> x);
    int initWeights();
    int printVector(std::vector<double> vec);
private:
    int neurons;
    int inputVectDim;
    double ** Wf;
    double ** Wi;
    double ** Wc;
    double ** Wo;
    double ** Wy;
    double ** biasArr; // bf bi bc bo
    double * by;
    
    
    std::vector<double> fWeightVec;
    std::vector<double> iWeightVec;
    std::vector<double> cWeightVec;
    std::vector<double> oWeightVec;
    std::vector<double> yWeightVec;
    
    double out_t;
    
    double f_t;
    double i_t;
    double c_dash_t;
    double c_t;
    double o_t;
    
    std::vector<double> deltaX_t;
    std::vector<double> deltaOut_0;
    
    std::vector<double> * deltaGateArray;
    

};

#endif /* LSTMNET_H */

