//
//  LinearRegressor.h
//  ml++
//
//  Created by Ronan Kelly on 12/25/21.
//

#ifndef LinearRegressor_h
#define LinearRegressor_h

#include <vector>

#include "DataFrame.h"
#include "Series.h"

class LinearRegressor {
    
private:
    
    //  Bias
    double b;
    
    //  Weights
    Series<double> w;
  
public:
    LinearRegressor();
    
    double bias() const;
    const Series<double> weights() const;
    
    void fit(std::vector<Series<double>> x, Series<double> y, int epochs = 1000, double learning_rate=0.003);
    Series<double> predict(std::vector<Series<double>> x) const;
};

#endif /* LinearRegressor_h */
