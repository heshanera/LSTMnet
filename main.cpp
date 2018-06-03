/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on April 8, 2018, 12:46 PM
 */

#include <vector>

#include "LSTMNet.h"
#include "DataProcessor.h"
#include "FileProcessor.h"

int univarPredicts() {
    
    int memCells = 5; // number of memory cells
    int trainDataSize = 300; // train data size
    int inputVecSize = 60; // input vector size
    int timeSteps = 60; // unfolded time steps
    float learningRate = 0.02;
    int predictions = 1580; // prediction points
    int iterations = 10; // training iterations with training data
    
    // Adding the time series in to a vector and preprocessing
    DataProcessor * dataproc;
    dataproc = new DataProcessor();
    FileProcessor * fileProc;
    fileProc = new FileProcessor();
    std::vector<double> timeSeries;
    
    
    ////////// Converting the CVS ////////////////////////    
    
        
//    fileProc->writeUniVariate("datasets/internetTrafficData.csv","datasets/InternetTraff.txt",2,1);
//    fileProc->writeUniVariate("datasets/monthlyReturnsOfValueweighted.csv","datasets/monthlyReturnsOfValueweighted.txt",2,1);
//    fileProc->writeUniVariate("datasets/treeAlmagreMountainPiarLocat.csv","datasets/treeAlmagreMountainPiarLocat.txt",2,1);
//    fileProc->writeUniVariate("datasets/dailyCyclistsAlongSudurlandsb.csv","datasets/dailyCyclistsAlongSudurlandsb.txt",2,1);
//    fileProc->writeUniVariate("datasets/totalPopulation.csv","datasets/totalPopulation.txt",2,1);
//    fileProc->writeUniVariate("datasets/numberOfUnemployed.csv","datasets/numberOfUnemployed.txt",2,1);
//    fileProc->writeUniVariate("datasets/data.csv","datasets/data.txt",2,1);
//    fileProc->writeUniVariate("datasets/monthlySunspotNumbers.csv","datasets/monthlySunspotNumbers.txt",2,1);
//    fileProc->writeUniVariate("datasets/dailyMinimumTemperatures.csv","datasets/dailyMinimumTemperatures.txt",2,1);    
    
    
    ///////////// Data Sets //////////////////////////////
    
    std::string datasets[] = {
        /* 0*/ "dummy2.txt",
        /* 1*/ "InternetTraff.txt",
        /* 2*/ "monthlyReturnsOfValueweighted.txt",
        /* 3*/ "treeAlmagreMountainPiarLocat.txt",
        /* 4*/ "dailyCyclistsAlongSudurlandsb.txt",
        /* 5*/ "totalPopulation.txt",
        /* 6*/ "numberOfUnemployed.txt",
        /* 7*/ "data.txt",
        /* 8*/ "monthlySunspotNumbers.txt",
        /* 9*/ "dailyMinimumTemperatures.txt",
        /*10*/ "hr2.txt"
    };
    
    std::string inFile = datasets[1];
    timeSeries = fileProc->read("datasets/univariate/input/"+inFile,1);
    timeSeries =  dataproc->process(timeSeries,1);
    
    // Creating the input vector Array
    std::vector<double> * input;
    input = new std::vector<double>[trainDataSize];
    std::vector<double> inputVec;
    
    for (int i = 0; i < trainDataSize; i++) {
        inputVec.clear();
        for (int j = 0; j < inputVecSize; j++) {
            inputVec.push_back(timeSeries.at(i+j));
        }
        inputVec =  dataproc->process(inputVec,0);
        input[i] = inputVec; 
    }
    
    
    // Creating the target vector using the time series 
    std::vector<double>::const_iterator first = timeSeries.begin() + inputVecSize;
    std::vector<double>::const_iterator last = timeSeries.begin() + inputVecSize + trainDataSize;
    std::vector<double> targetVector(first, last);
    
    // Training the LSTM net
    LSTMNet * lstm = new LSTMNet(memCells,inputVecSize);
    lstm->train(input, targetVector, trainDataSize, timeSteps, learningRate, iterations);
  
    // Open the file to write the time series predictions
    std::ofstream out_file;
    out_file.open("datasets/univariate/predictions/"+inFile,std::ofstream::out | std::ofstream::trunc);
    
    std::vector<double> inVec;
    input = new std::vector<double>[1];
    double result;
    double expected;
    //double MSE = 0;
    
    for (int i = 0; i < inputVecSize; i++) {
        out_file<<dataproc->postProcess(timeSeries.at(i))<<"\n";
    }
    
    std::cout << std::fixed;
    
    for (int i = 0; i < predictions; i++) {
        
        inVec.clear();
        for (int j = 0; j < inputVecSize; j++) {
            inVec.push_back(timeSeries.at(i+j));
        }
        
        inVec = dataproc->process(inVec,0);
        input[0] = inVec;
        
        result = lstm->predict(input);
        std::cout<<std::endl<<"result: "<<result<<std::endl;
        
        expected = timeSeries.at(i+inputVecSize+1);
        //MSE += std::pow(expected-result,2);
        
        result = dataproc->postProcess(result);
        out_file<<result-25000<<"\n";
        std::cout<<"result processed: "<<result<<std::endl<<std::endl;
    }
  
    //MSE /= predictions;
    //std::cout<<"Mean Squared Error: "<<MSE<<"\n";
    std::cout << std::scientific;
    return 0;
}

int multivarPredicts() {

    ///////////////////////// Multivariate time series data prediction ////////////////////////////////////
    
    int memCells = 10; // number of memory cells
    int inputVecSize = 5; // input vector size
    int trainDataSize = 5000; // train data size
    int timeSteps = 1; // data points used for one forward step
    float learningRate = 0.0001;
    int iterations = 10; // training iterations with training data
    int lines = 5000;
    
    DataProcessor * dataproc;
    dataproc = new DataProcessor();
    FileProcessor * fileProc;
    fileProc = new FileProcessor();
    
    int colIndxs[] = {0,0,1,1,1,1,1};
    int targetValCol = 7;
    
    std::vector<double> * timeSeries;
    timeSeries = fileProc->readMultivariate("datasets/occupancyData/datatraining.txt",lines,inputVecSize,colIndxs,targetValCol);
    
    // Creating the input vector Array
    std::vector<double> * input;
    input = new std::vector<double>[trainDataSize];    
    for (int i = 0; i < trainDataSize; i++) {
        input[i] = dataproc->process(timeSeries[i],0);
    }
    
    // Creating the target vector using the time series 
    std::vector<double>::const_iterator first = timeSeries[lines].begin();
    std::vector<double>::const_iterator last = timeSeries[lines].begin() + trainDataSize;
    std::vector<double> targetVector(first, last);
    for (std::vector<double>::iterator it = targetVector.begin(); it != targetVector.end(); ++it) {
        if (*it == 0) *it = -1;
    }    
    
    // Training the LSTM net
    LSTMNet * lstm = new LSTMNet(memCells,inputVecSize);    
    lstm->train(input, targetVector, trainDataSize, timeSteps, learningRate, iterations);
  
    // Predictions
    int predictions = 2000; // prediction points
    lines = 2000; // lines read from the files
    
    timeSeries = fileProc->readMultivariate("datasets/occupancyData/datatest.txt",lines,inputVecSize,colIndxs,targetValCol);
    input = new std::vector<double>[1];
    double result;
    double min = 0, max = 0;
    std::vector<double> resultVec;
    for (int i = 0; i < predictions; i++) {    
        input[0] = dataproc->process(timeSeries[i],0);
        result = lstm->predict(input);
        resultVec.push_back(result);
        //std::cout<<std::endl<<"result: "<<result<<"  ==>  expected: "<<timeSeries[lines].at(i)<<std::endl;
        
        if (i == 0){
            min = result;
            max = result;
        } else {
        
            if (min > result) min = result;
            if (max < result) max = result;
        }
    }
    std::cout<<"min: "<<min<<std::endl;
    std::cout<<"max: "<<max<<std::endl;
    
    double line = 0; //(min + max)/2;
    std::cout<<"margin: "<<line<<std::endl<<std::endl;
    
    
    int occu = 0, notoccu = 0;
    
    int corr = 0;
    int incorr = 0;
    
    int truePos = 0;
    int falsePos = 0;
    int trueNeg = 0;
    int falseNeg = 0;
    
    int corrNwMgn = 0;
    int incorrNwMgn = 0;
    
    // Open the file to write the time series predictions
    std::ofstream out_file;
    std::ofstream out_file2;
    out_file.open("datasets/multiResults.txt",std::ofstream::out | std::ofstream::trunc);
    out_file2.open("datasets/multiTargets.txt",std::ofstream::out | std::ofstream::trunc);
    
    for (int i = 0; i < predictions; i++) { 
        out_file<<timeSeries[lines].at(i)<<","<<resultVec.at(i)<<"\n";
        out_file2<<timeSeries[lines].at(i)<<",";
        if (timeSeries[lines].at(i) == 1) {
            out_file2<<1<<"\n";
        } else out_file2<<-1<<"\n";
        
        if ( (resultVec.at(i) > line) && (timeSeries[lines].at(i) == 1)) { 
            corr++;
            truePos++;
            occu++;
        } else if ( (resultVec.at(i) <= line) && (timeSeries[lines].at(i) == 0)) {
            corr++;
            trueNeg++;
            notoccu++;
        } else if ( (resultVec.at(i) <= line) && (timeSeries[lines].at(i) == 1)) { 
            incorr++; 
            falseNeg++;
            occu++;
        } else if ( (resultVec.at(i) > line) && (timeSeries[lines].at(i) == 0)) { 
            incorr++; 
            falsePos++;
            notoccu++;
        }
        //std::cout<<resultVec.at(i)<<" ------ "<<timeSeries[lines].at(i)<<"\n";
        
    }
    
    std::cout<<std::endl;
    
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Data "<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Occupied: "<<occu<<std::endl;
    std::cout<<"NotOccupied: "<<notoccu<<std::endl<<std::endl;
    
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"margin: "<<line<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Correct predictions: "<<corr<<std::endl;
    std::cout<<"Incorrect predictions: "<<incorr<<std::endl<<std::endl;
    
    std::cout<<"True Positive: "<<truePos<<std::endl;
    std::cout<<"True Negative: "<<trueNeg<<std::endl;
    std::cout<<"False Positive: "<<falsePos<<std::endl;
    std::cout<<"False Negative: "<<falseNeg<<std::endl;
    
    std::cout<<std::endl<<"Accuracy: "<<(corr/(double)predictions)*100<<"%"<<std::endl<<std::endl;
    
    
    line = (min + max)/2;
    occu = 0;
    notoccu = 0;
    corr = 0;
    incorr = 0;
    truePos = 0;
    falsePos = 0;
    trueNeg = 0;
    falseNeg = 0;
    
    for (int i = 0; i < predictions; i++) {    
        if ( (resultVec.at(i) > line) && (timeSeries[lines].at(i) == 1)) { 
            corr++;
            truePos++;
            occu++;
        } else if ( (resultVec.at(i) <= line) && (timeSeries[lines].at(i) == 0)) {
            corr++;
            trueNeg++;
            notoccu++;
        } else if ( (resultVec.at(i) <= line) && (timeSeries[lines].at(i) == 1)) { 
            incorr++; 
            falseNeg++;
            occu++;
        } else if ( (resultVec.at(i) > line) && (timeSeries[lines].at(i) == 0)) { 
            incorr++; 
            falsePos++;
            notoccu++;
        }
        
        
        
        if (line > 0) {
            if ( (resultVec.at(i) <= line) && (resultVec.at(i) > 0)) {
                if (timeSeries[lines].at(i) == 0) {
                    corrNwMgn++;
                } else incorrNwMgn++;
            }
        } else {
            if ( (resultVec.at(i) > line) && (resultVec.at(i) < 0)) {
                if (timeSeries[lines].at(i) == 1) {
                    corrNwMgn++;
                } else incorrNwMgn++;
            }
        }
        
    }
    
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"margin: "<<line<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Correct predictions: "<<corr<<std::endl;
    std::cout<<"Incorrect predictions: "<<incorr<<std::endl<<std::endl;
    
    std::cout<<"True Positive: "<<truePos<<std::endl;
    std::cout<<"True Negative: "<<trueNeg<<std::endl;
    std::cout<<"False Positive: "<<falsePos<<std::endl;
    std::cout<<"False Negative: "<<falseNeg<<std::endl;
    
    std::cout<<std::endl<<"Accuracy: "<<(corr/(double)predictions)*100<<"%"<<std::endl<<std::endl;
    
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Within the new margin and 0"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Correct: "<<corrNwMgn<<std::endl;
    std::cout<<"Incorrect: "<<incorrNwMgn<<std::endl<<std::endl<<std::endl;
    
    return 0;
}


int main() {

    // predicting univariate time series
    univarPredicts();
    
    // predicting multivariate series
    //multivarPredicts();

}
