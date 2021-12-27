
#include "../include/MinMaxScaler.h"

    MinMaxScaler::MinMaxScaler(Series<double> data) {

        double max = data.max();
        double min = data.min();

        this->_min = min;
        this->_max = max;
    }

    Series<double> MinMaxScaler::normalize(Series<double> unnormalized) {

        std::vector<double> scaled;

        for (const double &x: unnormalized) {
            scaled.push_back((x - _min) / (_max - _min));
        }
        
        return Series(scaled);
    }

    Series<double> MinMaxScaler::revert(Series<double> normalized) {
        std::vector<double> scaled;

        for (const double &x: normalized) {
            double reverted = (x * (_max - _min)) + _min;
            scaled.push_back(reverted);
        }
        
        return Series(scaled);
    }