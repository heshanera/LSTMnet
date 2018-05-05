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
#include <array>
//#include <functional>


class LSTMNet {
public:
    LSTMNet(int memCells,int inputVecSize);
    LSTMNet(const LSTMNet& orig);
    virtual ~LSTMNet();
    
    int train(std::vector<double> * input, std::vector<double> output, int trainDataSize, int timeSteps, float learningRate, int iterations);
    double predict(std::vector<double> * input);

    
private:
    int forward(std::vector<double> * input, int timeSteps);
    int backward(std::vector<double> output, int timeSteps);
    double sigmoid(double x);
    std::vector<double> sigmoid(std::vector<double> x);
    int initWeights();
    int clearVectors();
    int printVector(std::vector<double> vec);
    
private:
    int memCells;
    int inputVectDim;
    int timeSteps;
    
    std::vector<double> * aWeightVecArr;
    std::vector<double> * iWeightVecArr;
    std::vector<double> * fWeightVecArr;
    std::vector<double> * oWeightVecArr;
    
    double * aBiasArr;
    double * iBiasArr;
    double * fBiasArr;
    double * oBiasArr;
    
    std::vector<double> * memCellOutArr;
    std::vector<double> * memCellStateArr;
    
    std::vector<double> * aGateVecArr;
    std::vector<double> * iGateVecArr;
    std::vector<double> * fGateVecArr;
    std::vector<double> * oGateVecArr;
    
    std::vector<double> * aGateDeltaVecArr;
    std::vector<double> * iGateDeltaVecArr;
    std::vector<double> * fGateDeltaVecArr;
    std::vector<double> * oGateDeltaVecArr;
    
    std::vector<double> * xDeltaVecArr;
    
    std::vector<double> DeltaOutVec;
    
    std::vector<double> * aDeltaWeightVecArr;
    std::vector<double> * iDeltaWeightVecArr;
    std::vector<double> * fDeltaWeightVecArr;
    std::vector<double> * oDeltaWeightVecArr;
    
    
    /**
     * data structures used for the prediction
     */
    int noOfIns; // number of inputs given to the trained net to predict
    std::vector<double> * input2; // vector array created using the prediction inputs
    std::vector<double> output2; // target vector of the inputs given to predict
    
};

#endif /* LSTMNET_H */

