/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on April 8, 2018, 12:46 PM
 */

#include <cstdlib>
#include <vector>

#include "LSTMNet.h"
#include "DataProcessor.h"
#include "FileProcessor.h"

/*
 * 
 */
int main(int argc, char** argv) {

    
    int dataSize = 300; // train data size
    
    int memCells = 5; // number of memory cells
    int inputVecSize = 100; // input vector size
    int trainDataSize = dataSize; 
    int timeSteps = 100;
    float learningRate = 0.0005;
    int predictions = 1000; // prediction points
    int iterations = 5; // training iterations with training data
    
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
    
//////////////////////////////////////////////////////    
    
//    timeSeries = fileProc->read("datasets/dummy2.txt",1);
//    timeSeries = fileProc->read("datasets/InternetTraff.txt",1);
//    timeSeries = fileProc->read("datasets/monthlyReturnsOfValueweighted.txt",1);
//    timeSeries = fileProc->read("datasets/treeAlmagreMountainPiarLocat.txt",1);
//    timeSeries = fileProc->read("datasets/dailyCyclistsAlongSudurlandsb.txt",1);
//    timeSeries = fileProc->read("datasets/totalPopulation.txt",1);
//    timeSeries = fileProc->read("datasets/numberOfUnemployed.txt",1);
//    timeSeries = fileProc->read("datasets/data.txt",1);
    timeSeries = fileProc->read("datasets/monthlySunspotNumbers.txt",1);
//    timeSeries = fileProc->read("datasets/dailyMinimumTemperatures.txt",1);
    
    timeSeries =  dataproc->process(timeSeries,1);
    
    
    // Creating the input vector Array
    std::vector<double> * input;
//    dataSize += inputVecSize;
    input = new std::vector<double>[dataSize];
    std::vector<double> inputVec;
    
    for (int i = 0; i < dataSize; i++) {
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
    out_file.open("datasets/results.txt",std::ofstream::out | std::ofstream::trunc);
    
    std::vector<double> inVec;
    input = new std::vector<double>[1];
    double result;
    
    for (int i = 0; i < inputVecSize; i++) {
        out_file<<dataproc->postProcess(timeSeries.at(i))<<"\n";
    }
    
    for (int i = 0; i < predictions; i++) {
        
        inVec.clear();
        for (int j = 0; j < inputVecSize; j++) {
            inVec.push_back(timeSeries.at(i+j));
        }
        
        inVec = dataproc->process(inVec,0);
        input[0] = inVec;
        
        std::vector<double> tmpOut;
//        if ((i+1)%timeSteps == 0) {
//            std::vector<double>::const_iterator first = timeSeries.begin() + (timeSteps*(i/timeSteps));
//            std::vector<double>::const_iterator last = timeSeries.begin() + (timeSteps*(i/timeSteps) + timeSteps);
//            std::vector<double> outVec(first, last);
//            tmpOut = outVec;
//        }

        result = lstm->predict(input,tmpOut);
        std::cout<<std::endl<<"result: "<<result<<std::endl;
        result = dataproc->postProcess(result);
        std::cout<<"result processed: "<<result<<std::endl<<std::endl;
        
        out_file<<result/3 - 100<<"\n";
    }
    return 0;
}

