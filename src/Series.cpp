//
//  Series.cpp
//  ml++
//
//  Created by Ronan Kelly on 12/24/21.
//

#include "../include/Series.h"
#include <math.h>
#include <string>

template<typename T> Series<T>::Series(std::initializer_list<T> list) {
    this->internal_vec = std::make_unique<std::vector<T>>(list);
}

template<typename T> Series<T>::Series() : Series({ }) { }

template<typename T> Series<T>::Series(const std::vector<T> &list) {
    this->internal_vec = std::make_unique<std::vector<T>>(list);
}

template<typename T> Series<T>::Series(T value, size_t size) {
    
    this->internal_vec = std::make_unique<std::vector<T>>();
    
    for (int i = 0; i < size; i++) {
        this->internal_vec->push_back(value);
    }
}

template<typename T> Series<T> Series<T>::zeros(size_t size) {
    
    return Series(0, size);
}

template<typename T> Series<T> Series<T>::ones(size_t size) {
    
    return Series(1, size);
}

template<typename T> size_t Series<T>::size() const {
    
    return this->internal_vec->size();
}

template<typename T> T Series<T>::sum() const {
    
    T sum = 0;
    
    for (const T &val: *this->internal_vec) {
        sum += val;
    }
    
    return sum;
}

template<typename T> double Series<T>::avg() const {
    
    return static_cast<double>(this->sum()) / static_cast<double>(this->size());
}

template<typename T> double Series<T>::std() const {
    
    double mean = this->avg();
    double numerator = 0;
    
    for (const T &val: *this->internal_vec) {
        numerator += pow(val - mean, 2);
    }
    
    return sqrt(numerator / this->size());
}

template<typename T> T Series<T>::min() const {
    
    T min = *this->internal_vec->begin();
    
    for (T val: *this->internal_vec) {
        
        if (val < min) {
            min = val;
        }
    }
    
    return min;
}

template<typename T> T Series<T>::max() const {
    
    T max = *this->internal_vec->begin();
    
    for (T val: *this->internal_vec) {
        
        if (val > max) {
            max = val;
        }
    }
    
    return max;
}

template<typename T> typename std::vector<T>::iterator Series<T>::begin() {
    return this->internal_vec->begin();
}

template<typename T> typename std::vector<T>::iterator Series<T>::end() {
    return this->internal_vec->end();
}

template<typename T> T Series<T>::operator [] (int index) {
    return (*this->internal_vec)[index];
}

template<typename T> Series<T> Series<T>::operator+(const T &scalar) {
    return perform_operator_scalar(scalar, operation::add);
}

template<typename T> Series<T> Series<T>::operator-(const T &scalar) {
    return perform_operator_scalar(scalar, operation::subtract);
}

template<typename T> Series<T> Series<T>::operator*(const T &scalar) {
    return perform_operator_scalar(scalar, operation::multiply);
}

template<typename T> Series<T> Series<T>::operator/(const T &scalar) {
    return perform_operator_scalar(scalar, operation::divide);
}

template<typename T> Series<T> Series<T>::operator+(const Series<T> &other) {
    return perform_operator_other(other, operation::add);
}

template<typename T> Series<T> Series<T>::operator-(const Series<T> &other) {
    return perform_operator_other(other, operation::subtract);
}

template<typename T> Series<T> Series<T>::operator*(const Series<T> &other) {
    return perform_operator_other(other, operation::multiply);
}

template<typename T> Series<T> Series<T>::operator/(const Series<T> &other) {
    return perform_operator_other(other, operation::divide);
}

template<typename T> Series<T> Series<T>::series_pow(const T &scalar) {
    
    std::vector<T> new_series;
    
    for (const T &val: *this->internal_vec) {
        new_series.push_back(static_cast<T>(pow(val, scalar)));
    }
    
    return Series(new_series);
}

template<typename T> Series<T> Series<T>::series_sqrt() {
    
    std::vector<T> new_series;
    
    for (const T &val: *this->internal_vec) {
        new_series.push_back(static_cast<T>(sqrt(val)));
    }
    
    return Series(new_series);
}

template<typename T> Series<T> Series<T>::series_abs() {
    
    std::vector<T> new_series;
    
    for (const T &val: *this->internal_vec) {
        new_series.push_back(static_cast<T>(abs(val)));
    }
    
    return Series(new_series);
}

template<typename T> const std::vector<T> Series<T>::to_vector() const {
    return *this->internal_vec;
}

template<typename T> std::vector<Series<T>> Series<T>::transpose(std::vector<Series<T>> series) {
    
    std::vector<Series<T>> transposed;
    
    for (int i = 0; i < (int)series[0].size(); i++) {
        
        std::vector<T> temp;
        
        for (Series<T> s: series) {
            
            temp.push_back(s[i]);
        }
        
        transposed.push_back(temp);
    }
    
    return transposed;
};

//  We have to do this :(
template class Series<int>;
template class Series<float>;
template class Series<double>;
