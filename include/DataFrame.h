//
//  DataFrame.h
//  ml++
//
//  Created by Ronan Kelly on 12/24/21.
//

#ifndef DataFrame_h
#define DataFrame_h

#include <map>
#include <vector>
#include <set>

#include "Series.h"

template<typename T> class DataFrame {
    using dataframe = std::map<std::string, Series<T>>;
    
private:
    std::unique_ptr<dataframe> internal_df;
    
public:
    
    //  Initializers
    DataFrame();
    DataFrame(const dataframe &structure);
    DataFrame(const std::map<std::string, std::vector<T>> &dict);
    static DataFrame from_csv(const std::string &path);
    
    //  Info
    std::pair<size_t, size_t> shape() const;
    std::vector<std::string> keys() const;
    std::string info() const;
    
    //  Operators and getters
    std::vector<Series<T>> get(const std::vector<std::string> &keys);
    Series<T> operator [] (const std::string &key);
    
    //  Mutating members
    void drop(const std::string &key);
    
    
};

#endif /* DataFrame_h */
