

#include "../include/Series.h"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {

    Series s1 = { 1, 2, 3 };
    Series s2 = { 5, 6, 7 };

    cout << "Test 1" << endl;
    cout << (s1 + s2) + 4 << endl << endl;

    Series squares = Series<double>::uniform(5, 5);

    cout << "Test 2" << endl;
    cout << squares.series_pow(2) << endl << endl;

    Series sqrts = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };

    cout << "Test 3" << endl;
    cout << sqrts.series_sqrt() << endl << endl;

    return 0;
}