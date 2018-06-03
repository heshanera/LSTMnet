/* 
 * File:   MemoryCell.cpp
 * Author: heshan
 * 
 * Created on April 8, 2018, 2:11 PM
 */

#include "LSTMNet.h"

LSTMNet::LSTMNet(int memCells, int inputVecSize) {
    this->memCells = memCells;
    this->inputVectDim = inputVecSize;
    
    noOfIns = 0;
}

LSTMNet::LSTMNet(const LSTMNet& orig) { }

LSTMNet::~LSTMNet() { }

int LSTMNet::forward(std::vector<double> * input, int timeSteps) {
    
    std::vector<double> X;
    double a_t, i_t, f_t, o_t, state, out;
    for(int j = 0; j < memCells; j++){
        
        for(int i = 0; i < timeSteps; i++) {
            
            X = input[i];
            X.push_back(memCellOutArr[j][i]); // 0: id (number) of the memCell

            a_t = std::inner_product(
                aWeightVecArr[j].begin(), 
                aWeightVecArr[j].end(), 
                X.begin(), 0.0
            );
            i_t = std::inner_product(
                iWeightVecArr[j].begin(), 
                iWeightVecArr[j].end(), 
                X.begin(), 0.0
            );
            f_t = std::inner_product(
                fWeightVecArr[j].begin(), 
                fWeightVecArr[j].end(), 
                X.begin(), 0.0
            );
            o_t = std::inner_product(
                oWeightVecArr[j].begin(), 
                oWeightVecArr[j].end(), 
                X.begin(), 0.0
            );
            a_t = tanh(a_t + aBiasArr[j]); // 0: id (number) of the memCell
            i_t = sigmoid(i_t + iBiasArr[j]); // 0: id (number) of the memCell
            f_t = sigmoid(f_t + fBiasArr[j]); // 0: id (number) of the memCell
            o_t = sigmoid(o_t + oBiasArr[j]); // 0: id (number) of the memCell

            state = (a_t * i_t) + (f_t * memCellStateArr[0].at(i));
            memCellStateArr[j].push_back(state);

            out = tanh(state) * o_t;
            memCellOutArr[j].push_back(out);

            aGateVecArr[j].push_back(a_t);
            iGateVecArr[j].push_back(i_t);
            fGateVecArr[j].push_back(f_t);
            oGateVecArr[j].push_back(o_t);
        }
        memCellStateArr[j].push_back(0);
        fGateVecArr[j].push_back(0);
    }    
    
    return 0;
}

int LSTMNet::backward(std::vector<double> output, int timeSteps) {
    
    double DeltaErr, deltaOut, deltaState_t;
    double delta_a_t, delta_i_t, delta_f_t, delta_o_t;
    double memCellOutSum;
    for (int j = 0; j < memCells; j++) {
        for (int i = timeSteps-1; i >= 0; i--) {
            memCellOutSum = 0;
            for (int p = 0; p < memCells; p++) {
                memCellOutSum += memCellOutArr[p].at(i);
            }
//            DeltaErr = memCellOutArr[j].at(i) - output.at(i); // 0: id (number) of the memCell
            DeltaErr = memCellOutSum - output.at(i);
            deltaOut = DeltaErr + DeltaOutVec.at(j); // 0: id (number) of the memCell
            deltaState_t = deltaOut * oGateVecArr[j].at(i) * // 0: id (number) of the memCell
                        (1- std::pow(tanh(memCellStateArr[j].at(i+1)),2)) + // 0: id (number) of the memCell
                        memCellStateArr[j].at(i+2) * fGateVecArr[j].at(i+1); // 0: id (number) of the memCell

            delta_a_t = deltaState_t * iGateVecArr[j].at(i) * (1- std::pow(aGateVecArr[j].at(i),2));
            delta_i_t = deltaState_t * aGateVecArr[j].at(i) * iGateVecArr[j].at(i) * (1-iGateVecArr[j].at(i));
            delta_f_t = deltaState_t * memCellStateArr[j].at(i) * fGateVecArr[j].at(i) * (1-fGateVecArr[j].at(i));
            delta_o_t = deltaState_t * tanh(memCellStateArr[j].at(i+1)) * oGateVecArr[j].at(i) * (1-oGateVecArr[j].at(i));

            aGateDeltaVecArr[j].push_back(delta_a_t); // 0: id (number) of the memCell
            iGateDeltaVecArr[j].push_back(delta_i_t); // 0: id (number) of the memCell
            fGateDeltaVecArr[j].push_back(delta_f_t); // 0: id (number) of the memCell
            oGateDeltaVecArr[j].push_back(delta_o_t); // 0: id (number) of the memCell

            DeltaOutVec.at(j) =
                aWeightVecArr[j].at(inputVectDim) * delta_a_t +
                iWeightVecArr[j].at(inputVectDim) * delta_i_t +
                fWeightVecArr[j].at(inputVectDim) * delta_f_t +
                oWeightVecArr[j].at(inputVectDim) * delta_o_t;

        }
    }
    return 0;
}

int LSTMNet::train(std::vector<double> * input, std::vector<double> output, int trainDataSize, int timeSteps, float learningRate, int iterations){
    
    if ( iterations > 1 ) {
        int dataSize = trainDataSize;
        int itr;
        trainDataSize = trainDataSize*iterations;
        std::vector<double> * extdInput;
        extdInput = new std::vector<double>[trainDataSize];
        for (int i = 0; i < iterations; i++){
            itr = i*dataSize;
            for (int j = 0; j < dataSize; j++) {
                extdInput[itr+j] = input[j];
            }
            if (i == (iterations -1)) break;
            output.insert(output.end(), output.begin(), output.end());
        }
        input = new std::vector<double>[trainDataSize];
        input = extdInput;
    }
    
    this->timeSteps = timeSteps;
    // array used for the predictions.
    input2 = new std::vector<double>[timeSteps]; // no of time steps per training iteration
 
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
        
        forward(inVec,timeSteps);
        backward(outVec,timeSteps);
        
        for (int p = 0; p < memCells; p++) {
            deltaVecPos = timeSteps-1;
            for (int j = 0; j < timeSteps; j++) {
            
                inputVec = input[j+index];
                inputVec.push_back(memCellOutArr[p].at(j));

                delta_a_t = aGateDeltaVecArr[p].at(deltaVecPos);
                delta_i_t = iGateDeltaVecArr[p].at(deltaVecPos);
                delta_f_t = fGateDeltaVecArr[p].at(deltaVecPos);
                delta_o_t = oGateDeltaVecArr[p].at(deltaVecPos);
                deltaVecPos--;

                int wPos = 0;
                for (std::vector<double>::iterator it = inputVec.begin(); it != inputVec.end(); ++it) {
                    aDeltaWeightVecArr[p].at(wPos) += *it * delta_a_t;
                    iDeltaWeightVecArr[p].at(wPos) += *it * delta_i_t;
                    fDeltaWeightVecArr[p].at(wPos) += *it * delta_f_t;
                    oDeltaWeightVecArr[p].at(wPos) += *it * delta_o_t;
                    wPos++;
                }
                delta_bias_a_t += delta_a_t;
                delta_bias_i_t += delta_i_t;
                delta_bias_f_t += delta_f_t;
                delta_bias_o_t += delta_o_t;
            }
            aBiasArr[p] -= (delta_bias_a_t * learningRate);
            iBiasArr[p] -= (delta_bias_i_t * learningRate);       
            fBiasArr[p] -= (delta_bias_f_t * learningRate);
            oBiasArr[p] -= (delta_bias_o_t * learningRate);
            
        }
          
        index += timeSteps;
        for(int j = 0; j < memCells; j++) {
            
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
    return 0;
}

int LSTMNet::initWeights() {
    
    aWeightVecArr = new std::vector<double>[memCells];
    iWeightVecArr = new std::vector<double>[memCells];
    fWeightVecArr = new std::vector<double>[memCells];
    oWeightVecArr = new std::vector<double>[memCells];
    
    aBiasArr = new double[memCells];
    iBiasArr = new double[memCells];
    fBiasArr = new double[memCells];
    oBiasArr = new double[memCells];
    
    memCellOutArr = new std::vector<double>[memCells];
    memCellStateArr = new std::vector<double>[memCells];
    
    aGateVecArr = new std::vector<double>[memCells];
    iGateVecArr = new std::vector<double>[memCells];
    fGateVecArr = new std::vector<double>[memCells];
    oGateVecArr = new std::vector<double>[memCells];
    
    aGateDeltaVecArr = new std::vector<double>[memCells];
    iGateDeltaVecArr = new std::vector<double>[memCells];
    fGateDeltaVecArr = new std::vector<double>[memCells];
    oGateDeltaVecArr = new std::vector<double>[memCells];
    
    aDeltaWeightVecArr = new std::vector<double>[memCells];
    iDeltaWeightVecArr = new std::vector<double>[memCells];
    fDeltaWeightVecArr = new std::vector<double>[memCells];
    oDeltaWeightVecArr = new std::vector<double>[memCells];
    
    xDeltaVecArr = new std::vector<double>[memCells];
    
    int weightVecSize = inputVectDim + 1; 
    
    for(int i = 0; i < memCells; i++) {
        
        std::vector<double>  aWeightVec;
        aWeightVec.clear();
        std::vector<double>  iWeightVec;
        iWeightVec.clear();
        std::vector<double>  fWeightVec;
        fWeightVec.clear();
        std::vector<double>  oWeightVec;
        oWeightVec.clear();

        double w, max, min, diff;
        //****//
        min = -0.01;
        max = 0.01;
        //****//
//        min = sqrt(6/(inputVectDim + 1)) * -1;
//        max = sqrt(6/(inputVectDim + 1));     
        //****//
//        min = -1/sqrt(inputVectDim); 
//        max = 1/sqrt(inputVectDim);
        
        diff = max - min;
//        srand(time(NULL));  // if not random numbers are generated in the same order
        for(int j = 0; j < weightVecSize; j++) {
            w= (double)rand() / RAND_MAX;
            aWeightVec.push_back(min + w * diff); // Min + w * (Max - Min);
            w= (double)rand() / RAND_MAX;
            iWeightVec.push_back(min + w * diff); // Min + w * (Max - Min);
            w= (double)rand() / RAND_MAX;
            fWeightVec.push_back(min + w * diff); // Min + w * (Max - Min);
            w= (double)rand() / RAND_MAX;
            oWeightVec.push_back(min + w * diff); // Min + w * (Max - Min);
        }
        
        aWeightVecArr[i] = aWeightVec;
        iWeightVecArr[i] = iWeightVec;
        fWeightVecArr[i] = fWeightVec;
        oWeightVecArr[i] = oWeightVec;
        
        // generating random bias
        
        aBiasArr[i] = ( -0.01 + ((double)rand() / RAND_MAX) * 0.02);
        iBiasArr[i] = ( -0.01 + ((double)rand() / RAND_MAX) * 0.02);
        fBiasArr[i] = ( -0.01 + ((double)rand() / RAND_MAX) * 0.02);
        oBiasArr[i] = ( -0.01 + ((double)rand() / RAND_MAX) * 0.02);
        
        std::vector<double>  memCellOutVec;
        memCellOutVec.push_back(0);
        memCellOutArr[i] = memCellOutVec;
        
        std::vector<double>  memCellStateVec;
        memCellStateVec.push_back(0);
        memCellStateArr[i] = memCellStateVec;
        
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

    for(int i = 0; i < memCells; i++) {
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
        
        double out = memCellOutArr[i].back();
        memCellOutArr[i].clear();
        memCellOutArr[i].push_back(out);
    }        
    return 0;
}

double LSTMNet::predict(std::vector<double> * input) {

    forward(input, 1);
//    std::cout<<"\n"<<memCellOutArr[0].at(0)<<"\n";
//    std::cout<<"\n"<<memCellOutArr[0].at(1)<<"\n";
    
//    printVector(memCellOutArr[0]);
//    input2[noOfIns] = input[0];    
//    noOfIns++;
    
    double result = 0;
    for (int i = 0; i < memCells; i++) {
        result += *(memCellOutArr[i].end()-1);
    }
    
//    output2.push_back(result);
//    if (noOfIns == timeSteps) {
//        printVector(memCellOutArr[0]);
//        double out = memCellOutArr[0].front();
//        memCellOutArr[0].clear();
//        memCellOutArr[0].push_back(out);
//        noOfIns = 0;
//        train(input2, output, timeSteps, timeSteps, 0.095);
//    }
 
    return result;
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
    return 0;
}