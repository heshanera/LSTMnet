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

    
//    int dataSize = 500; // train data size
//    
//    int memCells = 8; // number of memory cells
//    int inputVecSize = 30; // input vector size
//    int trainDataSize = dataSize; 
//    int timeSteps = 30;
//    float learningRate = 0.01;
//    int predictions = 1000; // prediction points
//    int iterations = 5; // training iterations with training data
//    
//    // Adding the time series in to a vector and preprocessing
//    DataProcessor * dataproc;
//    dataproc = new DataProcessor();
//    FileProcessor * fileProc;
//    fileProc = new FileProcessor();
//    std::vector<double> timeSeries;
//    
//    
//////////// Converting the CVS ////////////////////////    
//    
//        
////    fileProc->writeUniVariate("datasets/internetTrafficData.csv","datasets/InternetTraff.txt",2,1);
////    fileProc->writeUniVariate("datasets/monthlyReturnsOfValueweighted.csv","datasets/monthlyReturnsOfValueweighted.txt",2,1);
////    fileProc->writeUniVariate("datasets/treeAlmagreMountainPiarLocat.csv","datasets/treeAlmagreMountainPiarLocat.txt",2,1);
////    fileProc->writeUniVariate("datasets/dailyCyclistsAlongSudurlandsb.csv","datasets/dailyCyclistsAlongSudurlandsb.txt",2,1);
////    fileProc->writeUniVariate("datasets/totalPopulation.csv","datasets/totalPopulation.txt",2,1);
////    fileProc->writeUniVariate("datasets/numberOfUnemployed.csv","datasets/numberOfUnemployed.txt",2,1);
////    fileProc->writeUniVariate("datasets/data.csv","datasets/data.txt",2,1);
////    fileProc->writeUniVariate("datasets/monthlySunspotNumbers.csv","datasets/monthlySunspotNumbers.txt",2,1);
////    fileProc->writeUniVariate("datasets/dailyMinimumTemperatures.csv","datasets/dailyMinimumTemperatures.txt",2,1);    
//    
////////////////////////////////////////////////////////    
//    
////    timeSeries = fileProc->read("datasets/dummy2.txt",1);
//    timeSeries = fileProc->read("datasets/InternetTraff.txt",1);
////    timeSeries = fileProc->read("datasets/monthlyReturnsOfValueweighted.txt",1);
////    timeSeries = fileProc->read("datasets/treeAlmagreMountainPiarLocat.txt",1);
////    timeSeries = fileProc->read("datasets/dailyCyclistsAlongSudurlandsb.txt",1);
////    timeSeries = fileProc->read("datasets/totalPopulation.txt",1);
////    timeSeries = fileProc->read("datasets/numberOfUnemployed.txt",1);
////    timeSeries = fileProc->read("datasets/data.txt",1);
////    timeSeries = fileProc->read("datasets/monthlySunspotNumbers.txt",1);
////    timeSeries = fileProc->read("datasets/dailyMinimumTemperatures.txt",1);
//    
//    timeSeries =  dataproc->process(timeSeries,1);
//    
//    
//    // Creating the input vector Array
//    std::vector<double> * input;
////    dataSize += inputVecSize;
//    input = new std::vector<double>[dataSize];
//    std::vector<double> inputVec;
//    
//    for (int i = 0; i < dataSize; i++) {
//        inputVec.clear();
//        for (int j = 0; j < inputVecSize; j++) {
//            inputVec.push_back(timeSeries.at(i+j));
//        }
//       
//        inputVec =  dataproc->process(inputVec,0);
//        input[i] = inputVec; 
//    }
//    
//    
//    // Creating the target vector using the time series 
//    std::vector<double>::const_iterator first = timeSeries.begin() + inputVecSize;
//    std::vector<double>::const_iterator last = timeSeries.begin() + inputVecSize + trainDataSize;
//    std::vector<double> targetVector(first, last);
//    
//    // Training the LSTM net
//    LSTMNet * lstm = new LSTMNet(memCells,inputVecSize);
//    lstm->train(input, targetVector, trainDataSize, timeSteps, learningRate, iterations);
//  
//    // Open the file to write the time series predictions
//    std::ofstream out_file;
//    out_file.open("datasets/results.txt",std::ofstream::out | std::ofstream::trunc);
//    
//    std::vector<double> inVec;
//    input = new std::vector<double>[1];
//    double result;
//    
//    for (int i = 0; i < inputVecSize; i++) {
//        out_file<<dataproc->postProcess(timeSeries.at(i))<<"\n";
//    }
//    
//    for (int i = 0; i < predictions; i++) {
//        
//        inVec.clear();
//        for (int j = 0; j < inputVecSize; j++) {
//            inVec.push_back(timeSeries.at(i+j));
//        }
//        
//        inVec = dataproc->process(inVec,0);
//        input[0] = inVec;
//        
//        result = lstm->predict(input);
//        std::cout<<std::endl<<"result: "<<result<<std::endl;
//        result = dataproc->postProcess(result);
//        std::cout<<"result processed: "<<result<<std::endl<<std::endl;
//        
//        out_file<<result<<"\n";
//    }
    
    ///////////////////////// Multivariate time series data prediction ////////////////////////////////////
    
    int memCells = 10; // number of memory cells
    int inputVecSize = 5; // input vector size
    int trainDataSize = 10; // train data size
    int timeSteps = 5; // data points used for one forward step
    float learningRate = 0.5;
    int predictions = 5000; // prediction points
    int iterations = 5; // training iterations with training data
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
//    dataproc->printVector(targetVector);
    
    // Training the LSTM net
    LSTMNet * lstm = new LSTMNet(memCells,inputVecSize);    
    lstm->train(input, targetVector, trainDataSize, timeSteps, learningRate, iterations);
  
    input = new std::vector<double>[1];
    double result;
    
    double min = 0, max = 0;
    
    std::vector<double> resultVec;
    
    for (int i = 0; i < predictions; i++) {    
        input[0] = dataproc->process(timeSeries[i],0);
        result = lstm->predict(input);
        resultVec.push_back(result);
//        std::cout<<std::endl<<"result: "<<result<<"  ==>  expected: "<<timeSeries[lines].at(i)<<std::endl;
        
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
    
    double line = (min + max)/2;
    std::cout<<"margin: "<<line<<std::endl<<std::endl;
    
    int corr = 0;
    int incorr = 0;
    
    int occu = 0, notoccu = 0;
    
    for (int i = 0; i < predictions; i++) {    
        if ( (resultVec.at(i) > line) && (timeSeries[lines].at(i) == 1)) { 
            corr++;
            occu++;
        } else if ( (resultVec.at(i) <= line) && (timeSeries[lines].at(i) == 0)) {
            corr++;
            notoccu++;
        } else { 
//            std::cout<<resultVec.at(i)<<" ------ "<<timeSeries[lines].at(i)<<"\n";
            incorr++; 
        }
//        std::cout<<resultVec.at(i)<<" ------ "<<timeSeries[lines].at(i)<<"\n";
        
    }
    
    std::cout<<std::endl;
    
    std::cout<<"correct: "<<corr<<std::endl;
    std::cout<<"Incorrect: "<<incorr<<std::endl<<std::endl;
    
    std::cout<<"Occupied: "<<occu<<std::endl;
    std::cout<<"Not Occupied: "<<notoccu<<std::endl;
    
    return 0;
}

