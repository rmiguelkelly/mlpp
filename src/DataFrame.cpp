//
//  DataFrame.cpp
//  ml++
//
//  Created by Ronan Kelly on 12/24/21.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>

#include "../include/Series.h"
#include "../include/DataFrame.h"

template<typename T> DataFrame<T>::DataFrame() {
    
    this->internal_df = std::make_unique<dataframe>();
}

template<typename T> DataFrame<T>::DataFrame(const dataframe &structure) {
    
    this->internal_df = std::make_unique<dataframe>(structure);
}

template<typename T> DataFrame<T>::DataFrame(const std::map<std::string, std::vector<T>> &dict) {
    
    this->internal_df = std::make_unique<dataframe>();
    
    for (const auto &val: dict) {
        (*this->internal_df)[val.first] = val.second;
    }
}

std::vector<std::string> parse_header(const std::string line) {
    
    std::vector<std::string> headers;
    
    char c_string[line.size()];
    
    memcpy(c_string, line.c_str(), line.size());
    
    char *token = strtok(c_string, ",");
    
    while (token != NULL) {
        
        headers.push_back(token);
        
        token = strtok(NULL, ",");
    }
    
    return headers;
}

template<typename T> DataFrame<T> DataFrame<T>::from_csv(const std::string &path) {
    
    std::ifstream handle(path.c_str());
    
    if (!handle.is_open()) {
        std::cerr << "Unable to find file" << std::endl;
        throw std::exception();
    }
    
    std::string current;
    
    std::getline(handle, current);
    
    auto headers = parse_header(current);
    std::map<std::string, std::vector<T>> mapped;
    
    for (const auto &str: headers) {
        mapped[str] = { };
    }
    
    while (std::getline(handle, current)) {
        
        char c_string[current.size()];
        
        memcpy(c_string, current.c_str(), current.size());
        
        char *token = strtok(c_string, ",");
        
        int index = 0;
        while (token != NULL) {
            
            T val = static_cast<T>(atof(token));
            
            mapped[headers[index]].push_back(val);
            
            token = strtok(NULL, ",");
            index++;
        }
    }
    
    
    handle.close();
    
    return DataFrame(mapped);
}

////  Info
template<typename T> std::pair<size_t, size_t> DataFrame<T>::shape() const {
    
    size_t x = this->internal_df->size();
    
    if (x == 0) {
        return std::make_pair(0, 0);
    }
    
    size_t y = (*this->internal_df->begin()).second.size();
    
    return std::make_pair(x, y);
}

template<typename T> std::vector<std::string> DataFrame<T>::keys() const {

    std::vector<std::string> keys;
    
    for (const auto &pair: *this->internal_df) {
        keys.push_back(pair.first);
    }
    
    return keys;
}

template<typename T> std::string DataFrame<T>::info() const {
    char buffer[512];
    
    auto s = this->shape();
    size_t size = sprintf(buffer, "<DataFrame size=(%lu, %lu)>", s.first, s.second);
    buffer[size] = 0;
    
    return std::string(buffer);
}

//  Operators
template<typename T>Series<T> DataFrame<T>::operator [] (const std::string &key) {
    return (*this->internal_df)[key];
}

template<typename T> std::vector<Series<T>> DataFrame<T>::get(const std::vector<std::string> &keys) {
    
    std::vector<Series<T>> series;
    
    for (const auto &key: keys) {
        series.push_back((*this->internal_df)[key]);
    }
    
    return series;
}

//  Mutating members
template<typename T> void DataFrame<T>::drop(const std::string &key) {
    this->internal_df->erase(key);
}


//  We have to do this :(
template class DataFrame<int>;
template class DataFrame<float>;
template class DataFrame<double>;
