//
//  main.cpp
//  ml++
//
//  Created by Ronan Kelly on 12/24/21.
//

#include <iostream>
#include <filesystem>

#include "../include/Series.h"
#include "../include/DataFrame.h"

#include "../include/LinearRegressor.h"

double predict(const LinearRegressor &model, Series<double> x) {
    Series<double> w = model.weights();
    return (w * x).sum() + model.bias();
}

int main(int argc, const char * argv[]) {

    std::string current_path = std::filesystem::current_path();
    std::string csv_path = "/samples/sample-single-feature.csv";

    auto df = DataFrame<double>::from_csv(current_path.append(csv_path));
    
    auto y = df["Labe"];
    auto x = df.get({ "Feature1", "Feature2" });
    
    LinearRegressor model;
    model.fit(x, y, 20000);
    
    printf(">> %.3f\n", predict(model, { 1, 1 }));
    
    
    return 0;
}
