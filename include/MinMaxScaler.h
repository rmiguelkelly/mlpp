//
//  Series.h
//  ml++
//
//  Created by Ronan Kelly on 12/24/21.
//

#ifndef MinMaxScaler_h
#define MinMaxScaler_h

#include "../include/Series.h"

class MinMaxScaler {

private:
    double _min, _max;

public:
    //  When called, sets the min and max
    explicit MinMaxScaler(Series<double> data);

    Series<double> normalize(Series<double> unnormalized);
    Series<double> revert(Series<double> normalized);
};


#endif