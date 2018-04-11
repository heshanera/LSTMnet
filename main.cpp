/* 
 * File:   main.cpp
 * Author: heshan
 *
 * Created on April 8, 2018, 12:46 PM
 */

#include <cstdlib>

#include "LSTMNet.h"

/*
 * 
 */
int main(int argc, char** argv) {

    
    LSTMNet * lstm = new LSTMNet();
//    lstm->test();
    lstm->train(1);

    
    return 0;
}

