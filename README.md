## LSTM network

The LSTM network is implemented with memory blocks containing one memory cell in each block. input layer is fully connected to the hidden layer. The weights for the network are randomly initialized. All the gates in a memory cell have bias values and they are initialized randomly and adjusted while training the network. Input vector for the network is the previous data points of the time series. Size of this input vector can be adjusted. The number of training timesteps to the future, the number of training iterations and the learning rate of the network can be adjusted accordingly.


## Network Architecture

![structure](https://github.com/heshanera/LSTMnet/blob/master/imgs/LSTMnetStructure.png)


## Training the network

training the network first started with a single memory block and then increase the number of memory blocks to increase the accuracy of the predictions. input vector size is increased to 60 and trained the network for first 200 points in the time series with 5 training iterations.Before feeding to the network the vectors are normalized.
