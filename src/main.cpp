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
#include "../include/MinMaxScaler.h"
#include "../include/LinearRegressor.h"

double predict(const LinearRegressor &model, Series<double> x) {
    Series<double> w = model.weights();
    return (w * x).sum() + model.bias();
}

int main(int argc, const char * argv[]) {

    std::string current_path = std::filesystem::current_path();
    std::string csv_path = "/samples/sample-housing-data.csv";

    auto df = DataFrame<double>::from_csv(current_path.append(csv_path));
    
    //  The scaler for the price (or whatever label we want to predict)
    MinMaxScaler price_scaler(df["Price"]);

    auto y = price_scaler.normalize(df["Price"]);
    auto x = df.get({ "SqFt", "Bedrooms", "Bathrooms", "Offers" });

    //  Each feature needs its own scaler
    std::vector<MinMaxScaler> feature_scalers;

    for (int i = 0; i < x.size(); i++) {

        //  Create a MinMaxScaler for each feature and store it to predict non-normalized values
        MinMaxScaler scaler(x[i]);

        //  Normalize the features
        x[i] = scaler.normalize(x[i]);
        feature_scalers.push_back(scaler);
    }
    
    LinearRegressor model;
    model.fit(x, y, 5000);

    //  To test, lets create a tuple
    //  Represents a house with 1790 sqft, 2 Bedrooms, 2 Bathrooms and 2 Offers
    Series<double> entry = { 3250, 3, 3, 4 };
    
    std::vector<double> normalized_entries;

    //  (x - min) / (max - min)
    for (int i = 0; i < entry.size(); i++) {
        normalized_entries.push_back(feature_scalers[i].normalize({ entry[i] })[0]);
    }

    Series<double> X = normalized_entries;
    
    double y_pred_norm = (X * model.weights()).sum() + model.bias();

    std::cout << price_scaler.revert({ y_pred_norm })[0] << std::endl;

    return 0;
}
