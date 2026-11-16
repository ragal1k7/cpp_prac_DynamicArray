#pragma once
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <cmath>

template <typename T>
class DynamicArray {
private:
    T* data_;
    int size_;

    void validateValue(T value) {
        if constexpr (std::is_integral_v<T>) {
            if (value < -100 || value > 100) {
                throw std::invalid_argument("Значение должно быть в диапазоне [-100, 100]");
            }
        }
    }

    void validateIndex(int index) const {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Индекс массива вне допустимого диапазона");
        }
    }

public:
    explicit DynamicArray(int size) : data_(nullptr), size_(size) {
        if (size < 0) {
            throw std::invalid_argument("Размер массива не может быть отрицательным");
        }
        if (size_ > 0) {
            data_ = new T[size_]{};
        }
    }

    DynamicArray(const DynamicArray& other) : data_(nullptr), size_(other.size_) {
        if (size_ > 0) {
            data_ = new T[size_];
            for (int i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    ~DynamicArray() {
        delete[] data_;
    }

    // Задание 1: Оператор [] через класс-посредник 
    class Proxy {
    private:
        DynamicArray& arr_;
        int index_;
    public:
        Proxy(DynamicArray& arr, int index) : arr_(arr), index_(index) {}
        
        Proxy& operator=(const T& value) {
            arr_.set(index_, value);
            return *this;
        }
        
        operator T() const {
            return arr_.get(index_);
        }
    };

    Proxy operator[](int index) {
        validateIndex(index);
        return Proxy(*this, index);
    }

    T operator[](int index) const {
        validateIndex(index);
        return data_[index];
    }

    // Задание 2: Операторы сравнения 
    bool operator==(const DynamicArray& other) const {
        if (size_ != other.size_) return false;
        for (int i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) return false;
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    // Задание 3: Составные операторы 
    DynamicArray& operator+=(const DynamicArray& other) {
        for (int i = 0; i < size_; ++i) {
            T otherValue = i < other.size_ ? other.data_[i] : T{};
            data_[i] += otherValue;
        }
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        for (int i = 0; i < size_; ++i) {
            T otherValue = i < other.size_ ? other.data_[i] : T{};
            data_[i] -= otherValue;
        }
        return *this;
    }

    DynamicArray& operator+=(T value) {
        validateValue(value);
        for (int i = 0; i < size_; ++i) {
            data_[i] += value;
        }
        return *this;
    }

    DynamicArray& operator-=(T value) {
        validateValue(value);
        for (int i = 0; i < size_; ++i) {
            data_[i] -= value;
        }
        return *this;
    }

    // Задание 4: Итераторы
    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }

    void set(int index, T value) {
        validateIndex(index);
        validateValue(value);
        data_[index] = value;
    }

    T get(int index) const {
        validateIndex(index);
        return data_[index];
    }

    int size() const {
        return size_;
    }

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        os << "{ ";
        for (int i = 0; i < arr.size_; ++i) {
            os << arr.data_[i] << (i + 1 < arr.size_ ? ", " : " ");
        }
        os << "}";
        return os;
    }
};

template <typename T>
double distance(const DynamicArray<T>& a, const DynamicArray<T>& b) {
    if constexpr (!std::is_arithmetic_v<T>) {
        throw std::bad_typeid();
    } else {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Размеры массивов должны совпадать");
        }
        double sum = 0.0;
        for (int i = 0; i < a.size(); ++i) {
            double diff = static_cast<double>(a.get(i)) - static_cast<double>(b.get(i));
            sum += diff * diff;
        }
        return std::sqrt(sum);
    }
}