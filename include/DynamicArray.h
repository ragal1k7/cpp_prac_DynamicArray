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

    void append(T value) {
        validateValue(value);
        T* expanded = new T[size_ + 1];
        for (int i = 0; i < size_; ++i) {
            expanded[i] = data_[i];
        }
        expanded[size_] = value;
        delete[] data_;
        data_ = expanded;
        ++size_;
    }

    void add(const DynamicArray& other) {
        for (int i = 0; i < size_; ++i) {
            T otherValue = i < other.size_ ? other.data_[i] : T{};
            data_[i] += otherValue;
        }
    }

    void subtract(const DynamicArray& other) {
        for (int i = 0; i < size_; ++i) {
            T otherValue = i < other.size_ ? other.data_[i] : T{};
            data_[i] -= otherValue;
        }
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        os << "{ ";
        for (int i = 0; i < arr.size_; ++i) {
            os << arr.data_[i] << (i + 1 < arr.size_ ? ", " : " ");
        }
        os << "}";
        return os;
    }
};

// Функция нахождения расстояния между массивами
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