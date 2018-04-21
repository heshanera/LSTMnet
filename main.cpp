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

    DataProcessor * dataproc;
    dataproc = new DataProcessor();
    
    FileProcessor * fileProc = new FileProcessor();
    
    std::vector<double> output;
//    output = fileProc->read("datasets/dummy.txt",1);
    
    int dataSize = 120;
    
    std::ofstream in_file;
    in_file.open("datasets/inputs.txt",std::ofstream::out | std::ofstream::trunc);
    double tmp = 0.1;
    for (int i = 0; i < dataSize; i+=6) {
        
        output.push_back(tmp);
//        in_file<<tmp<<"\n";
        output.push_back(tmp+0.1);
//        in_file<<(tmp+0.1)<<"\n";
        output.push_back(tmp+0.2);
//        in_file<<(tmp+0.2)<<"\n";
        output.push_back(tmp+0.3);
//        in_file<<(tmp+0.3)<<"\n";
        output.push_back(tmp+0.2);
//        in_file<<(tmp+0.2)<<"\n";
        output.push_back(tmp+0.1);
//        in_file<<(tmp+0.1)<<"\n";
        tmp += 0.1;
        
    }
    
    output =  dataproc->process(output,1);
    for (int i = 0; i < dataSize; i++) {
        in_file<<output.at(i)<<"\n";
    }
    
    std::vector<double> * input;
    input = new std::vector<double>[dataSize];
    std::vector<double> inputVec;
    
    int sec;
    
    for (int i = 0; i < dataSize; i++) {
        inputVec.clear();
        
        inputVec.push_back(0);
        inputVec.push_back(0);
        
        inputVec.push_back(i/120);
//        std::cout<<i/120<<' ';
        
        inputVec.push_back((i/2)%60);
//        std::cout<<(i/2)%60<<' ';
        
        if (i%2 == 0) inputVec.push_back(0);
        else inputVec.push_back(5);
//        std::cout<<i%2<<' '<<'\n';
        
//        std::cout<<"***********************************\n";
        dataproc->printVector(inputVec);
        inputVec =  dataproc->process(inputVec,0);
//        dataproc->printVector(inputVec);
        input[i] = inputVec;
//        std::cout<<"***********************************\n";
        
    }
    
    
    int neurons = 1;
    int inputVecSize = 5;
    int trainDataSize = dataSize;
    int timeSteps = 6;
    float learningRate = 0.095;
    
    double result;
    
    LSTMNet * lstm = new LSTMNet(neurons,inputVecSize);
    lstm->train(input, output, trainDataSize, timeSteps, learningRate);
  
    std::vector<double> vec1;
    input = new std::vector<double>[1];
    
//    fileProc->write("datasets/results.txt");
    
    std::ofstream out_file;
    out_file.open("datasets/results.txt",std::ofstream::out | std::ofstream::trunc);
    
    for (int i = 0; i < dataSize; i++) {
        vec1.clear();
        vec1.push_back(0);
        vec1.push_back(0);
        vec1.push_back(i/120);
        vec1.push_back((i/2)%60);
        if (i%2 == 0) vec1.push_back(0);
        else vec1.push_back(5);
        
        dataproc->printVector(vec1);
        vec1 =  dataproc->process(vec1,0);
        input[0] = vec1;
        
        result = lstm->predict(input);
        std::cout<<std::endl<<"result: "<<result<<std::endl;
//        result = dataproc->postProcess(result);
//        std::cout<<"result processed: "<<result<<std::endl<<std::endl;
        
        out_file<<result<<"\n";
        
        
        
    }
    
    
    
    
//    vec1.clear();
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1 =  dataproc->process(vec1,0);
//    input[0] = vec1;
//    
//    result = lstm->predict(input);
//    std::cout<<std::endl<<"result: "<<result<<std::endl;
//    std::cout<<"result processed: "<<dataproc->postProcess(result)<<std::endl<<std::endl;
//    
//    vec1.clear();
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(5);
//    vec1 =  dataproc->process(vec1,0);
//    input[0] = vec1;
//    
//    result = lstm->predict(input);
//    std::cout<<std::endl<<"result: "<<result<<std::endl;
//    std::cout<<"result processed: "<<dataproc->postProcess(result)<<std::endl<<std::endl;
//    
//    vec1.clear();
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(1);
//    vec1.push_back(0);
//    vec1 =  dataproc->process(vec1,0);
//    input[0] = vec1;
//    
//    result = lstm->predict(input);
//    std::cout<<std::endl<<"result: "<<result<<std::endl;
//    std::cout<<"result processed: "<<dataproc->postProcess(result)<<std::endl<<std::endl;
//    
//    
//    
//    vec1.clear();
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(1);
//    vec1.push_back(5);
//    vec1 =  dataproc->process(vec1,0);
//    input[0] = vec1;
//    
//    result = lstm->predict(input);
//    std::cout<<std::endl<<"result: "<<result<<std::endl;
//    std::cout<<"result processed: "<<dataproc->postProcess(result)<<std::endl<<std::endl;
//    
//    
//    vec1.clear();
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(0);
//    vec1.push_back(2);
//    vec1.push_back(0);
//    vec1 =  dataproc->process(vec1,0);
//    input[0] = vec1;
//    
//    result = lstm->predict(input);
//    std::cout<<std::endl<<"result: "<<result<<std::endl;
//    std::cout<<"result processed: "<<dataproc->postProcess(result)<<std::endl<<std::endl;
    
    return 0;
}

