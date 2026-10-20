#include "../include/DynamicArray.h"

#include <iostream>
#include <stdexcept>
#include <new>

int main() {
    try {
        DynamicArray arrayA(3);
        arrayA.set(0, 10);
        arrayA.set(1, 20);
        arrayA.set(2, 30);
        std::cout << "Массив arrayA: ";
        arrayA.print();
        std::cout << "arrayA[1] = " << arrayA.get(1) << "\n";

        DynamicArray copiedArray(arrayA);
        copiedArray.set(0, -10);
        std::cout << "Скопированный массив: ";
        copiedArray.print();
        std::cout << "Оригинальный массив: ";
        arrayA.print();

        arrayA.append(40);
        std::cout << "arrayA после добавления 40: ";
        arrayA.print();

        DynamicArray arrayB(2);
        arrayB.set(0, 1);
        arrayB.set(1, 2);
        arrayA.add(arrayB);
        std::cout << "arrayA после сложения с arrayB: ";
        arrayA.print();
        
        arrayA.subtract(arrayB);
        std::cout << "arrayA после вычитания arrayB: ";
        arrayA.print();

        std::cout << "\n--- Демонстрация исключений ---\n";

        try {
            std::cout << "Попытка вызвать get(99)...\n";
            arrayA.get(99);
        } catch (const std::out_of_range& e) {
            std::cout << "Поймано out_of_range: " << e.what() << "\n";
        }

        try {
            std::cout << "Попытка вызвать set(0, 150)...\n";
            arrayA.set(0, 150);
        } catch (const std::invalid_argument& e) {
            std::cout << "Поймано invalid_argument: " << e.what() << "\n";
        }

        try {
            std::cout << "Попытка выделить огромный массив...\n";
            DynamicArray hugeArray(2000000000); 
        } catch (const std::bad_alloc& e) {
            std::cout << "Поймано bad_alloc: " << e.what() << "\n";
        }

    } catch (const std::exception& error) {
        std::cerr << "Неожиданная ошибка: " << error.what() << "\n";
        return 1;
    }

    return 0;
}