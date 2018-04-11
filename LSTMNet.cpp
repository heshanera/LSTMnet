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

int LSTMNet::forward(std::vector<double> X_t) {
    
    /** toDO: Adding Bias*/
    
    neurons = 1;
    inputVectDim = 4;
   
    initWeights();
    
    std::vector<double> H_t_1;
    H_t_1.push_back(0.0123);
    
    double c_t_1 = 0;
    
    std::vector<double> X(H_t_1);
    
    X.insert( X.end(), X_t.begin(), X_t.end() );
    
    printVector(fWeightVec);
    printVector(iWeightVec);
    printVector(cWeightVec);
    printVector(oWeightVec);
    printVector(yWeightVec);
    std::cout<<"----------------------\n\n";
//    printVector(X);
    
    /*************************************/
    double tmpF = std::inner_product(fWeightVec.begin(), fWeightVec.end(), X.begin(),0.0);
    f_t = sigmoid(tmpF);
    
    double tmpI = std::inner_product(iWeightVec.begin(), iWeightVec.end(), X.begin(),0.0);
    i_t = sigmoid(tmpI);
    
    double tmpC_dash = std::inner_product(cWeightVec.begin(), cWeightVec.end(), X.begin(),0.0);
    c_dash_t = tanh(tmpC_dash);
    
    c_t = f_t * c_t_1 + i_t * c_dash_t; /**/
    
    double tmpO = std::inner_product(oWeightVec.begin(), oWeightVec.end(), X.begin(),0.0);
    o_t = sigmoid(tmpO);
    
    out_t = tanh(c_t) * o_t;
   
    
    
    
//    double h_t = o_t * tanh(c_t); /**/
//    
//    std::vector<double> H_t_vec;
//    H_t_vec.push_back(h_t);
//    double y_t = std::inner_product(yWeightVec.begin(), yWeightVec.end(), H_t_vec.begin(),0.0);
//    std::cout<<y_t;
//    
    /*************************************/
}

int LSTMNet::backward() {
    
    double expected = 0.456;
    double deltaError = out_t - expected;
    double state_0 = 0.1245;
    
    double c_t2 = 0;
    double f_t2 = 0;
    
    double deltaOut_last = 0;
    double deltaOut_1 = deltaError + deltaOut_last;
    double deltaState1 = deltaOut_1*o_t*(1- std::pow(tanh(c_t),2)) + c_t2 * f_t2;

    double delta_c_1 = deltaState1*i_t*(1- std::pow(c_dash_t,2));
    double delta_i_t = deltaState1*c_dash_t*i_t*(1-i_t);
    double delta_f_t = deltaState1*state_0*f_t*(1-f_t);
    double delta_o_t = deltaOut_1*tanh(c_t)*o_t*(1-o_t);
    
    int weightSize = fWeightVec.size(); 
    
    std::vector<double> * weightVecArray;
    weightVecArray = new std::vector<double>[weightSize];
    
    for(int i = 0; i < weightSize-1; i++){
        
        double tmpVal = cWeightVec.at(i) * delta_c_1 +
                        iWeightVec.at(i) * delta_i_t +
                        fWeightVec.at(i) * delta_f_t +
                        oWeightVec.at(i) * delta_o_t;
        
        deltaX_t.push_back(tmpVal);
    }
    
    double tmpVal = cWeightVec.at(weightSize-1) * delta_c_1 +
            iWeightVec.at(weightSize-1) * delta_i_t +
            fWeightVec.at(weightSize-1) * delta_f_t +
            oWeightVec.at(weightSize-1) * delta_o_t;
        
    deltaOut_0.push_back(tmpVal);
    
    
    deltaGateArray = new std::vector<double>[1]; // no of neurons
    
    std::vector<double> neuronDelta;
    neuronDelta.push_back(delta_c_1);
    neuronDelta.push_back(delta_i_t);
    neuronDelta.push_back(delta_f_t);
    neuronDelta.push_back(delta_o_t);
    
    deltaGateArray[0] = neuronDelta;
    
}

int LSTMNet::train(int t){
    
    std::vector<double> X_t;
    X_t.push_back(0.142);
    X_t.push_back(0.21231);
    X_t.push_back(0.03);
    X_t.push_back(0.123);
    
    forward(X_t);
    backward();
    
    std::vector<double> * deltaWeightArray;
    deltaWeightArray = new std::vector<double>[4]; // size of the input vector
    
    for (int j = 0; j < 4; j++) {
        std::vector<double> tmp (4,0); 
        deltaWeightArray[j] = tmp;
    }
    
    for (int i = 0; i < t; i++) {
        
        std::vector<double> neuronDelta;
        neuronDelta = deltaGateArray[i];
        
        int j = 0;
        for ( std::vector<double>::iterator it = X_t.begin(); it != X_t.end(); ++it) {
            
            std::vector<double> tmpVec(neuronDelta); 
            std::transform(
                tmpVec.begin(), 
                tmpVec.end(), 
                tmpVec.begin(), 
                std::bind1st(std::multiplies<double>(), *it)
            );
            
            printVector(tmpVec);
            std::transform(
                deltaWeightArray[j].begin(), 
                deltaWeightArray[j].end(), 
                tmpVec.begin(), deltaWeightArray[j].begin(), 
                std::plus<double>()
            );
            printVector(deltaWeightArray[j]);
            j++;
            
        }
        
    }
    
    
}

int LSTMNet::initWeights() {
    
//    int vectorSize = neurons + inputVectDim;
//    
//    Wf = new double*[vectorSize]; 
//    for(int i = 0; i < vectorSize; i++) {
//        Wf[i] = new double[neurons];
//        for(int j = 0; j < neurons; j++) {
//            double w = (double)rand() / RAND_MAX;
//            Wf[i][j] = -1 + w * 2; // Min + w * (Max - Min);
//            std::cout<<(-1 + w * 2)<<" ";
//        }
//        std::cout<<"\n";
//    }   
//    
//    Wi = new double*[vectorSize]; 
//    for(int i = 0; i < vectorSize; i++) {
//        Wi[i] = new double[neurons];
//        for(int j = 0; j < neurons; j++) {
//            double w = (double)rand() / RAND_MAX;
//            Wi[i][j] = -1 + w * 2; // Min + w * (Max - Min);
//            std::cout<<(-1 + w * 2)<<" ";
//        }
//        std::cout<<"\n";
//    }  
//    
//    Wc = new double*[vectorSize]; 
//    for(int i = 0; i < vectorSize; i++) {
//        Wc[i] = new double[neurons];
//        for(int j = 0; j < neurons; j++) {
//            double w = (double)rand() / RAND_MAX;
//            Wc[i][j] = -1 + w * 2; // Min + w * (Max - Min);
//            std::cout<<(-1 + w * 2)<<" ";
//        }
//        std::cout<<"\n";
//    }  
//    
//    Wo = new double*[vectorSize]; 
//    for(int i = 0; i < vectorSize; i++) {
//        Wo[i] = new double[neurons];
//        for(int j = 0; j < neurons; j++) {
//            double w = (double)rand() / RAND_MAX;
//            Wo[i][j] = -1 + w * 2; // Min + w * (Max - Min);
//            std::cout<<(-1 + w * 2)<<" ";
//        }
//        std::cout<<"\n";
//    }  
//    
//    Wy = new double*[neurons]; 
//    for(int i = 0; i < neurons; i++) {
//        Wy[i] = new double[inputVectDim];
//        for(int j = 0; j < inputVectDim; j++) {
//            double w = (double)rand() / RAND_MAX;
//            Wy[i][j] = -1 + w * 2; // Min + w * (Max - Min);
//            std::cout<<(-1 + w * 2)<<" ";
//        }
//        std::cout<<"\n";
//    } 
//    
//    biasArr = new double*[4];
//    for(int i = 0; i < 4; i++) {
//        biasArr[i] = new double[neurons];
//        for(int j = 0; j < neurons; j++) {
//            biasArr[i][j] = 0;
//            std::cout<<0<<" ";
//        }
//        std::cout<<"\n";
//    }
//    
//    by = new double[inputVectDim];
//    for(int j = 0; j < inputVectDim; j++) {
//        by[j] = 0;
//        std::cout<<0<<" ";
//    }
    int weightVecSize = inputVectDim + 1; 
    
    
    for(int j = 0; j < weightVecSize; j++) {
        double w;
        w= (double)rand() / RAND_MAX;
        fWeightVec.push_back(-1 + w * 2); // Min + w * (Max - Min);
        w= (double)rand() / RAND_MAX;
        iWeightVec.push_back(-1 + w * 2); // Min + w * (Max - Min);
        w= (double)rand() / RAND_MAX;
        cWeightVec.push_back(-1 + w * 2); // Min + w * (Max - Min);
        w= (double)rand() / RAND_MAX;
        oWeightVec.push_back(-1 + w * 2); // Min + w * (Max - Min);
    }
    
    for(int j = 0; j < inputVectDim; j++) {
        double w;
        w= (double)rand() / RAND_MAX;
        yWeightVec.push_back(-1 + w * 2); // Min + w * (Max - Min);
    }
    
    std::vector<double> fBias(neurons,0);
    
//    for (std::vector<double>::iterator it = weightVec.begin(); it != weightVec.end(); ++it)
//        std::cout << ' ' << *it;
//    std::cout << '\n';
    
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


int LSTMNet::test() {
    
    neurons = 1;
    inputVectDim = 4;
    
    initWeights();
}