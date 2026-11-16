#pragma once
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <cmath>
#include <utility> 

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

    // 1. Конструктор копирования 
    DynamicArray(const DynamicArray& other) : data_(nullptr), size_(other.size_) {
        if (size_ > 0) {
            data_ = new T[size_];
            for (int i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    // 2. Оператор присваивания копированием (Задание 1)
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) {
            return *this; 
        }
        
        T* newData = nullptr;
        if (other.size_ > 0) {
            newData = new T[other.size_];
            for (int i = 0; i < other.size_; ++i) {
                newData[i] = other.data_[i];
            }
        }
        
        delete[] data_;
        data_ = newData;
        size_ = other.size_;
        
        return *this;
    }

    // 3. Move-конструктор (Задание 2)
    DynamicArray(DynamicArray&& other) noexcept 
        : data_(other.data_), size_(other.size_) {
        // Забираем ресурсы, а источник обнуляем
        other.data_ = nullptr;
        other.size_ = 0;
    }

    // 4. Move-оператор присваивания (Задание 3)
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        
        delete[] data_;
        
        data_ = other.data_;
        size_ = other.size_;
        
        other.data_ = nullptr;
        other.size_ = 0;
        
        return *this;
    }

    ~DynamicArray() {
        delete[] data_;
    }

    // Всё, что было в Части 4
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