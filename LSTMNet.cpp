/* 
 * File:   MemoryCell.cpp
 * Author: heshan
 * 
 * Created on April 8, 2018, 2:11 PM
 */

#include "LSTMNet.h"

LSTMNet::LSTMNet(int neurons, int inputVecSize) {
    this->neurons = neurons;
    this->inputVectDim = inputVecSize;
}

LSTMNet::LSTMNet(const LSTMNet& orig) {
}

LSTMNet::~LSTMNet() {
}

int LSTMNet::forward(std::vector<double> * input, int timeSteps) {
    
    std::vector<double> X;
    double a_t, i_t, f_t, o_t, state, out;
    for(int i = 0; i < timeSteps; i++) {
        
        X = input[i];
        X.push_back(neuronOutArr[0][i]); // 0: id (number) of the neuron
        
        a_t = std::inner_product(
            aWeightVecArr[0].begin(), 
            aWeightVecArr[0].end(), 
            X.begin(), 0.0
        );
        i_t = std::inner_product(
            iWeightVecArr[0].begin(), 
            iWeightVecArr[0].end(), 
            X.begin(), 0.0
        );
        f_t = std::inner_product(
            fWeightVecArr[0].begin(), 
            fWeightVecArr[0].end(), 
            X.begin(), 0.0
        );
        o_t = std::inner_product(
            oWeightVecArr[0].begin(), 
            oWeightVecArr[0].end(), 
            X.begin(), 0.0
        );
        a_t = tanh(a_t + aBiasArr[0]); // 0: id (number) of the neuron
        i_t = sigmoid(i_t + iBiasArr[0]); // 0: id (number) of the neuron
        f_t = sigmoid(f_t + fBiasArr[0]); // 0: id (number) of the neuron
        o_t = sigmoid(o_t + oBiasArr[0]); // 0: id (number) of the neuron
        
        state = (a_t * i_t) + (f_t * neuronStateArr[0].at(i));
        neuronStateArr[0].push_back(state);
        
        out = tanh(state) * o_t;
        neuronOutArr[0].push_back(out);
        
        aGateVecArr[0].push_back(a_t);
        iGateVecArr[0].push_back(i_t);
        fGateVecArr[0].push_back(f_t);
        oGateVecArr[0].push_back(o_t);
    }
    neuronStateArr[0].push_back(0);
    fGateVecArr[0].push_back(0);
    
    return 0;
}

int LSTMNet::backward(std::vector<double> output, int timeSteps) {
    
    double DeltaErr, deltaOut, deltaState_t;
    double delta_a_t, delta_i_t, delta_f_t, delta_o_t;
    for (int i = timeSteps-1; i >= 0; i--) {
        DeltaErr = neuronOutArr[0].at(i) - output.at(i); // 0: id (number) of the neuron
        deltaOut = DeltaErr + DeltaOutVec.at(0); // 0: id (number) of the neuron
        deltaState_t = deltaOut * oGateVecArr[0].at(i) * // 0: id (number) of the neuron
                    (1- std::pow(tanh(neuronStateArr[0].at(i+1)),2)) + // 0: id (number) of the neuron
                    neuronStateArr[0].at(i+2) * fGateVecArr[0].at(i+1); // 0: id (number) of the neuron
        
        delta_a_t = deltaState_t * iGateVecArr[0].at(i) * (1- std::pow(aGateVecArr[0].at(i),2));
        delta_i_t = deltaState_t * aGateVecArr[0].at(i) * iGateVecArr[0].at(i) * (1-iGateVecArr[0].at(i));
        delta_f_t = deltaState_t * neuronStateArr[0].at(i) * fGateVecArr[0].at(i) * (1-fGateVecArr[0].at(i));
        delta_o_t = deltaState_t * tanh(neuronStateArr[0].at(i+1)) * oGateVecArr[0].at(i) * (1-oGateVecArr[0].at(i));

        aGateDeltaVecArr[0].push_back(delta_a_t); // 0: id (number) of the neuron
        iGateDeltaVecArr[0].push_back(delta_i_t); // 0: id (number) of the neuron
        fGateDeltaVecArr[0].push_back(delta_f_t); // 0: id (number) of the neuron
        oGateDeltaVecArr[0].push_back(delta_o_t); // 0: id (number) of the neuron
        
        DeltaOutVec.at(0) =
            aWeightVecArr[0].at(inputVectDim) * delta_a_t +
            iWeightVecArr[0].at(inputVectDim) * delta_i_t +
            fWeightVecArr[0].at(inputVectDim) * delta_f_t +
            oWeightVecArr[0].at(inputVectDim) * delta_o_t;
        
    }
    
}

int LSTMNet::train(std::vector<double> * input, std::vector<double> output, int trainDataSize, int timeSteps, float learningRate){
    
    initWeights();
    
    int trainingIterations = floor(trainDataSize / timeSteps);
    
    std::vector<double> inputVec;
    
    int index = 0;
    int deltaVecPos;
    double delta_a_t,delta_i_t,delta_f_t,delta_o_t;
    double delta_bias_a_t,delta_bias_i_t,delta_bias_f_t,delta_bias_o_t;
    
    std::vector<double> *inVec;
    
    
    for (int i = 0; i < trainingIterations; i++){
        
        inVec = input + (timeSteps*i);
        
        std::vector<double>::const_iterator first = output.begin() + (timeSteps*i);
        std::vector<double>::const_iterator last = output.begin() + (timeSteps*i + timeSteps);
        std::vector<double> outVec(first, last);
        
        forward(input,timeSteps);
        backward(outVec,timeSteps);
        
        deltaVecPos = timeSteps-1;
        for (int j = 0; j < timeSteps; j++) {
            
            inputVec = input[j+index];
            inputVec.push_back(neuronOutArr[0].at(j));

            delta_a_t = aGateDeltaVecArr[0].at(deltaVecPos);
            delta_i_t = iGateDeltaVecArr[0].at(deltaVecPos);
            delta_f_t = fGateDeltaVecArr[0].at(deltaVecPos);
            delta_o_t = oGateDeltaVecArr[0].at(deltaVecPos);
            deltaVecPos--;
            
            int wPos = 0;
            for (std::vector<double>::iterator it = inputVec.begin(); it != inputVec.end(); ++it) {
                aDeltaWeightVecArr[0].at(wPos) += *it * delta_a_t;
                iDeltaWeightVecArr[0].at(wPos) += *it * delta_i_t;
                fDeltaWeightVecArr[0].at(wPos) += *it * delta_f_t;
                oDeltaWeightVecArr[0].at(wPos) += *it * delta_o_t;
                wPos++;
            }
            
            delta_bias_a_t += delta_a_t;
            delta_bias_i_t += delta_i_t;
            delta_bias_f_t += delta_f_t;
            delta_bias_o_t += delta_o_t;
        }
        
        aBiasArr[0] -= (delta_bias_a_t * learningRate);
        iBiasArr[0] -= (delta_bias_i_t * learningRate);       
        fBiasArr[0] -= (delta_bias_f_t * learningRate);
        oBiasArr[0] -= (delta_bias_o_t * learningRate);
                
        index += timeSteps;
        
        for(int j = 0; j < neurons; j++) {
            
            std::transform(
                aDeltaWeightVecArr[j].begin(), 
                aDeltaWeightVecArr[j].end(), 
                aDeltaWeightVecArr[j].begin(), 
                std::bind1st(std::multiplies<double>(), 0.1)
            );
            std::transform(
                iDeltaWeightVecArr[j].begin(), 
                iDeltaWeightVecArr[j].end(), 
                iDeltaWeightVecArr[j].begin(), 
                std::bind1st(std::multiplies<double>(), 0.1)
            );
            std::transform(
                fDeltaWeightVecArr[j].begin(), 
                fDeltaWeightVecArr[j].end(), 
                fDeltaWeightVecArr[j].begin(), 
                std::bind1st(std::multiplies<double>(), 0.1)
            );
            std::transform(
                oDeltaWeightVecArr[j].begin(), 
                oDeltaWeightVecArr[j].end(), 
                oDeltaWeightVecArr[j].begin(), 
                std::bind1st(std::multiplies<double>(), 0.1)
            );
                    
            std::transform(
                aWeightVecArr[j].begin(), aWeightVecArr[j].end(), 
                aDeltaWeightVecArr[j].begin(), aWeightVecArr[j].begin(), 
                std::minus<double>()
            );
            std::transform(
                iWeightVecArr[j].begin(), iWeightVecArr[j].end(), 
                iDeltaWeightVecArr[j].begin(), iWeightVecArr[j].begin(), 
                std::minus<double>()
            );
            std::transform(
                fWeightVecArr[j].begin(), fWeightVecArr[j].end(), 
                fDeltaWeightVecArr[j].begin(), fWeightVecArr[j].begin(), 
                std::minus<double>()
            );
            std::transform(
                oWeightVecArr[j].begin(), oWeightVecArr[j].end(), 
                oDeltaWeightVecArr[j].begin(), oWeightVecArr[j].begin(), 
                std::minus<double>()
            );
            
        }
        
        clearVectors();
    }    
}

int LSTMNet::initWeights() {
    
    aWeightVecArr = new std::vector<double>[neurons];
    iWeightVecArr = new std::vector<double>[neurons];
    fWeightVecArr = new std::vector<double>[neurons];
    oWeightVecArr = new std::vector<double>[neurons];
    
    aBiasArr = new double[neurons];
    iBiasArr = new double[neurons];
    fBiasArr = new double[neurons];
    oBiasArr = new double[neurons];
    
    neuronOutArr = new std::vector<double>[neurons];
    neuronStateArr = new std::vector<double>[neurons];
    
    aGateVecArr = new std::vector<double>[neurons];
    iGateVecArr = new std::vector<double>[neurons];
    fGateVecArr = new std::vector<double>[neurons];
    oGateVecArr = new std::vector<double>[neurons];
    
    aGateDeltaVecArr = new std::vector<double>[neurons];
    iGateDeltaVecArr = new std::vector<double>[neurons];
    fGateDeltaVecArr = new std::vector<double>[neurons];
    oGateDeltaVecArr = new std::vector<double>[neurons];
    
    aDeltaWeightVecArr = new std::vector<double>[neurons];
    iDeltaWeightVecArr = new std::vector<double>[neurons];
    fDeltaWeightVecArr = new std::vector<double>[neurons];
    oDeltaWeightVecArr = new std::vector<double>[neurons];
    
    xDeltaVecArr = new std::vector<double>[neurons];
    
    int weightVecSize = inputVectDim + 1; 
    
    for(int i = 0; i < neurons; i++) {
        
        std::vector<double>  aWeightVec;
        aWeightVec.clear();
        std::vector<double>  iWeightVec;
        iWeightVec.clear();
        std::vector<double>  fWeightVec;
        fWeightVec.clear();
        std::vector<double>  oWeightVec;
        oWeightVec.clear();

        for(int j = 0; j < weightVecSize; j++) {
            double w;
            w= (double)rand() / RAND_MAX;
            aWeightVec.push_back(-1 + w * 2); // Min + w * (Max - Min);
            w= (double)rand() / RAND_MAX;
            iWeightVec.push_back(-1 + w * 2); // Min + w * (Max - Min);
            w= (double)rand() / RAND_MAX;
            fWeightVec.push_back(-1 + w * 2); // Min + w * (Max - Min);
            w= (double)rand() / RAND_MAX;
            oWeightVec.push_back(-1 + w * 2); // Min + w * (Max - Min);
        }
        
        aWeightVecArr[i] = aWeightVec;
        iWeightVecArr[i] = iWeightVec;
        fWeightVecArr[i] = fWeightVec;
        oWeightVecArr[i] = oWeightVec;
        
        // generating random bias
        
        aBiasArr[i] = ( -1 + ((double)rand() / RAND_MAX) * 2);
        iBiasArr[i] = ( -1 + ((double)rand() / RAND_MAX) * 2);
        fBiasArr[i] = ( -1 + ((double)rand() / RAND_MAX) * 2);
        oBiasArr[i] = ( -1 + ((double)rand() / RAND_MAX) * 2);
        
        std::vector<double>  neuronOutVec;
        neuronOutVec.push_back(0);
        neuronOutArr[i] = neuronOutVec;
        
        std::vector<double>  neuronStateVec;
        neuronStateVec.push_back(0);
        neuronStateArr[i] = neuronStateVec;
        
        std::vector<double>  aGateVec;
        aGateVecArr[i] = aGateVec;
        std::vector<double>  iGateVec;
        iGateVecArr[i] = iGateVec;
        std::vector<double>  fGateVec;
        fGateVecArr[i] = fGateVec;
        std::vector<double>  oGateVec;
        oGateVecArr[i] = oGateVec;
        
        DeltaOutVec.push_back(0);
        
        std::vector<double> aGateDeltaVec;
        aGateDeltaVecArr[i] = aGateDeltaVec;
        std::vector<double> iGateDeltaVec;
        iGateDeltaVecArr[i] = iGateDeltaVec;
        std::vector<double> fGateDeltaVec;
        fGateDeltaVecArr[i] = fGateDeltaVec;
        std::vector<double> oGateDeltaVec;
        oGateDeltaVecArr[i] = oGateDeltaVec;
        
        std::vector<double> xDeltaVec;
        xDeltaVecArr[i] = xDeltaVec;
        
        std::vector<double> aDeltaWeightVec(weightVecSize,0);
        aDeltaWeightVecArr[i] = aDeltaWeightVec;
        std::vector<double> iDeltaWeightVec(weightVecSize,0);
        iDeltaWeightVecArr[i] = iDeltaWeightVec;
        std::vector<double> fDeltaWeightVec(weightVecSize,0);
        fDeltaWeightVecArr[i] = fDeltaWeightVec;
        std::vector<double> oDeltaWeightVec(weightVecSize,0);
        oDeltaWeightVecArr[i] = oDeltaWeightVec;
        
    }
    return 0;
}

int LSTMNet::clearVectors() {

    for(int i = 0; i < neurons; i++) {
        aGateDeltaVecArr[i].clear();
        iGateDeltaVecArr[i].clear();
        fGateDeltaVecArr[i].clear();
        oGateDeltaVecArr[i].clear();

        int weightVecSize = inputVectDim + 1; 
        
        std::vector<double> aDeltaWeightVec(weightVecSize,0);
        aDeltaWeightVecArr[i] = aDeltaWeightVec;
        std::vector<double> iDeltaWeightVec(weightVecSize,0);
        iDeltaWeightVecArr[i] = iDeltaWeightVec;
        std::vector<double> fDeltaWeightVec(weightVecSize,0);
        fDeltaWeightVecArr[i] = fDeltaWeightVec;
        std::vector<double> oDeltaWeightVec(weightVecSize,0);
        oDeltaWeightVecArr[i] = oDeltaWeightVec;
        
        double out = neuronOutArr[i].back();
        neuronOutArr[i].clear();
        neuronOutArr[i].push_back(out);
    }        
        
    return 0;
}

int LSTMNet::predict(std::vector<double> * input) {

    forward(input, 1);
//    std::cout<<"\n"<<neuronOutArr[0].at(0)<<"\n";
//    std::cout<<"\n"<<neuronOutArr[0].at(1)<<"\n";
    
    printVector(neuronOutArr[0]);
    
    return 0;
}

double LSTMNet::sigmoid(double x) {
    return 1/(1 + std::pow (std::exp(1.0), -x));
}

std::vector<double> LSTMNet::sigmoid(std::vector<double> vec) {
    for ( std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
        *it = 1/(1 + std::pow (std::exp(1.0), -(*it)));
    }
    return vec;
}

int LSTMNet::printVector(std::vector<double> vec) {
    for (std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}