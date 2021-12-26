//
//  Series.h
//  ml++
//
//  Created by Ronan Kelly on 12/24/21.
//

#ifndef Series_h
#define Series_h

#include <vector>
#include <string>

//  This will serve as a wrapper around the vector structure
//  and give us methods to retrieve statistics such as standard deviation
//  and operators such as adding scalars and other frames
template<typename T> class Series {
private:
    std::shared_ptr<std::vector<T>> internal_vec;
    
    enum operation {
        add,
        subtract,
        multiply,
        divide
    };
    
    Series<T> perform_operator_scalar(T value, operation what) {
        std::vector<T> modified;
        
        for (auto val: *this->internal_vec) {
            T new_val;
            
            switch (what) {
                case operation::add:
                    new_val = val + value;
                    break;
                case operation::subtract:
                    new_val = val - value;
                    break;
                case operation::multiply:
                    new_val = val * value;
                    break;
                case operation::divide:
                    new_val = val / value;
                    break;
            }
            
            modified.push_back(new_val);
        }
        
        return Series(modified);
    }
    
    Series<T> perform_operator_other(Series<T> other, operation what) {
        
        if (this->size() != other.size()) {
            printf("Except: %lu != %lu\n", this->size(), other.size());
            throw std::exception();
        }
        
        std::vector<T> modified;
        
        for (int i = 0; i < this->size(); i++) {
            T new_val;
            
            T val = (*this->internal_vec)[i];
            T other_val = other[i];
            switch (what) {
                case operation::add:
                    new_val = val + other_val;
                    break;
                case operation::subtract:
                    new_val = val - other_val;
                    break;
                case operation::multiply:
                    new_val = val * other_val;
                    break;
                case operation::divide:
                    new_val = val / other_val;
                    break;
            }
            
            modified.push_back(new_val);
        }
        
        return Series(modified);
    }
    
public:
    Series();
    Series(std::initializer_list<T> list);
    Series(const std::vector<T> &list);
    
    //  Creates a list of size n filled with the specified value
    Series(T value, size_t size);
    
    //  Static helpers
    static Series<T> zeros(size_t size);
    static Series<T> ones(size_t size);
    
    //  Stats
    size_t size() const;
    T sum() const;
    double avg() const;
    double std() const;
    
    T min() const;
    T max() const;
    
    //Iterators
    typename std::vector<T>::iterator begin();
    typename std::vector<T>::iterator end();
    
    //  Operator overloading
    T operator [] (int index);
    
    Series<T> operator + (const T &scalar);
    Series<T> operator - (const T &scalar);
    Series<T> operator * (const T &scalar);
    Series<T> operator / (const T &scalar);
    
    Series<T> operator + (const Series<T> &other);
    Series<T> operator - (const Series<T> &other);
    Series<T> operator * (const Series<T> &other);
    Series<T> operator / (const Series<T> &other);
    
    Series<T> series_pow(const T &scalar);
    Series<T> series_sqrt();
    Series<T> series_abs();

    Series<T> copy();
    
    const std::vector<T> to_vector() const;
    
    friend std::ostream& operator << (std::ostream& os, const Series<T> &series) {
        os << std::string("<Series size=(") << series.size() << std::string("), objects=[");
        
        for (int i = 0; i < series.size(); i++) {
            os << (*series.internal_vec)[i];
            if (i < series.size() - 1) {
                os << std::string(", ");
            }
        }
        
        os << std::string("]>");
        
        return os;
    }
    
    static std::vector<Series<T>> transpose(std::vector<Series<T>> series);
};

#endif /* Series_h */
