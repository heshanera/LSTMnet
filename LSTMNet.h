/* 
 * File:   MemoryCell.h
 * Author: heshan
 *
 * Created on April 8, 2018, 2:11 PM
 */

#ifndef LSTMNET_H
#define LSTMNET_H

#include <iostream>
#include <cmath>

class LSTMNet {
public:
    LSTMNet();
    LSTMNet(const LSTMNet& orig);
    virtual ~LSTMNet();
    
    int forward();
    
    int test();
    
private:
    double forgetGate();
    double sigmoid(double x);
    int initWeights();
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
    

};

#endif /* LSTMNET_H */

