## LSTMnet

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://github.com/heshanera/LSTMnet/blob/master/LICENSE)&nbsp;&nbsp;
[![language](https://img.shields.io/badge/language-c%2B%2B-red.svg)](https://github.com/heshanera/IProc) &nbsp;&nbsp;


## LSTM network

The LSTM network is implemented with memory blocks containing one memory cell in each block. input layer is fully connected to the hidden layer. The weights for the network are randomly initialized. All the gates in a memory cell have bias values and they are initialized randomly and adjusted while training the network. Input vector for the network is the previous data points of the time series. Size of this input vector can be adjusted. The number of training timesteps to the future, the number of training iterations and the learning rate of the network can be adjusted accordingly.


## Network Architecture

![structure](https://github.com/heshanera/LSTMnet/blob/master/imgs/LSTMnetStructure.png)

## Creating A Network

###### initializing variables
```
int memCells = 5; // number of memory cells
int trainDataSize = 300; // train data size
int inputVecSize = 60; // input vector size
int timeSteps = 60; // unfolded time steps
float learningRate = 0.02; // leraning rate
int predictions = 1300; // prediction points
int iterations = 10; // training iterations with training data
```
###### Initializing the network
```
LSTMNet lstm(memCells,inputVecSize);
```
###### Training
```
lstm.train(input, targetVector, trainDataSize, timeSteps, learningRate, iterations);
```
###### Testing
```
double result;
result = lstm.predict(input);
```
