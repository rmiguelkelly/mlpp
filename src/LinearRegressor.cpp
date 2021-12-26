//
//  LinearRegressor.cpp
//  ml++
//
//  Created by Ronan Kelly on 12/25/21.
//

#include <iostream>
#include <stdio.h>
#include <vector>

#include "../include/LinearRegressor.h"

LinearRegressor::LinearRegressor() { }

//  The mean squared error loss function
double mse(Series<double> y_predict, Series<double> y_actual) {
    return (y_predict - y_actual).series_pow(2).sum() / y_predict.size();
}

//  Initialize an array with a set of uniform values
void init_array(double *array, size_t size, int value) {
    for (int i = 0; i < size; i++) {
        array[i] = value;
    }
}

//  From the features, perform batch gradient descent to fit the data to a model
//  Runtime complexity is O(EPOCHS * SAMPLES * FEATURES)
void LinearRegressor::fit(std::vector<Series<double>> x, Series<double> y, int epochs, double learning_rate) {
    
    //  We will be using batch gradient descent for now...
    
    //  Transpose our matrix
    x = Series<double>::transpose(x);
    
    size_t N = y.size();    //  the size of our dataset
    size_t F = x[0].size(); //  the number of features
    
    //  Our weights and bias in the scope of this function
    double _b = 0;
    double _w[F];
    
    //  Initialize the weights to 1
    init_array(_w, F, 1);
    
    //  Iterate updating the weights and biases X times
    for (int _ = 0; _ < epochs; _++) {
        
        //  Go through each sample for batch gradient descent, we can
        //  change this to stochastic GD to limit the iterations....
        
        //  ======= START: The partial derivitive of the bias and weights initialized here ====
        double df_dw[F]; //  the derivitive in respect to the weight[s]
        init_array(df_dw, F, 0);
        
        double df_db = 0; //  the derivitive in repsect to the bias
        //  ======= END: The partial derivitive of the bias and weights initialized here ====
        
        //  For each sample....
        for (int i = 0; i < N; i++) {
            
            double weighted_sum_for_row = 0;
            
            for (int j = 0; j < F; j++) {
                weighted_sum_for_row += _w[j] * x[i][j];
            }
            
            weighted_sum_for_row += _b;
            
            df_db += -2.0 * (y[i] - weighted_sum_for_row);
            
            for (int j = 0; j < F; j++) {
                df_dw[j] += -2 * x[i][j] * (y[i] - weighted_sum_for_row);
            }
        }
        
        //  After computing the sum, divide by N
        df_db /= N;
        
        //  After computing the sum, divide by N for each weight
        for (int i = 0; i < F; i++) {
            df_dw[i] /= N;
        }
        
        //  Update the weights and bias
        for (int i = 0; i < F; i++) {
            _w[i] -= learning_rate * df_dw[i];
        }
        
        _b -= learning_rate * df_db;
    }
    
    //  === Update the class weights and bias ===
    std::vector<double> w_tmp;
    
    for (int i = 0; i < F; i++) {
        w_tmp.push_back(_w[i]);
    }
    
    this->w = w_tmp;
    this->b = _b;
    // ==============
}

Series<double> LinearRegressor::predict(std::vector<Series<double>> x) const {
    
    std::vector<double> predictions;
    
    x = Series<double>::transpose(x);
    
    for (auto tuple: x) {
        double y_pred = (tuple * this->w).sum() + this->b;
        predictions.push_back(y_pred);
    }
    
    return Series<double>(predictions);
}

double LinearRegressor::bias() const {
    return this->b;
}

const Series<double> LinearRegressor::weights() const{
    return this->w;
}

