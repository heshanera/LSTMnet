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
#include <ctime>

//#include <functional>


class LSTMNet {
public:
    LSTMNet(int memCells,int inputVecSize);
    LSTMNet(const LSTMNet& orig);
    virtual ~LSTMNet();
    
    /**
    * 
    * @param input: training data set
    * @param output: target values
    * @param trainDataSize: training data size
    * @param timeSteps: unfolding time steps
    * @param learningRate
    * @param iterations: training iterations
    * @return 0
    */
    int train(std::vector<double> * input, std::vector<double> output, int trainDataSize, int timeSteps, float learningRate, int iterations);
    /**
    * predict a future point using a input vector of size n
    * 
    * input: {t-n,...,t-2,t-1,t}
    * result: {t+1} 
    * 
    * @param input: input vector for he prediction
    * @return result: predicted value
    */
    double predict(std::vector<double> * input);

    
private:
    /**
     * Forward Propagation of the network
     *  
     * @param input: input vector
     * @param timeSteps: unfolded time steps in the input vector
     * @return 0
     */
    int forward(std::vector<double> * input, int timeSteps);
    /**
     * Backward Propagation of the network
     * 
     * @param output: output from the forward propagation
     * @param timeSteps: unfolded time steps
     * @return 0
     */
    int backward(std::vector<double> output, int timeSteps);
    /**
     * Initialize the weights and bias values for the gates
     * Random initialization
     * 
     * @return 0
     */
    int initWeights();
    /**
     * Clear Vectors
     * 
     * @return 0
     */
    int clearVectors();
    /**
     * print the given vector
     * 
     * @param vec: vector
     * @return 0 
     */
    int printVector(std::vector<double> vec);
    /**
     * Sigmoid function
     * 
     * @param x
     * @return value
     */
    double sigmoid(double x);
    /**
     * Sigmoid function
     * 
     * @param x: input vector
     * @return vector
     */
    std::vector<double> sigmoid(std::vector<double> x);
    
private:
    int memCells;
    int inputVectDim;
    int timeSteps;
    
    // weight vector arrays
    std::vector<double> * aWeightVecArr;
    std::vector<double> * iWeightVecArr;
    std::vector<double> * fWeightVecArr;
    std::vector<double> * oWeightVecArr;
    
    // bias value arrays
    double * aBiasArr;
    double * iBiasArr;
    double * fBiasArr;
    double * oBiasArr;
    
    std::vector<double> * memCellOutArr;
    std::vector<double> * memCellStateArr;
    
    // gate output value arrays
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

