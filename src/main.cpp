#include "../include/DynamicArray.h"
#include <iostream>
#include <string>

int main() {
    try {
        std::cout << "=== Часть 3: Шаблоны ===\n\n";

        // 1. Работа с целочисленным массивом
        DynamicArray<int> arrInt(3);
        arrInt.set(0, 10);
        arrInt.set(1, 20);
        arrInt.set(2, 30);
        std::cout << "Массив int: " << arrInt << "\n";

        // 2. Работа с нечисловым массивом (строки)
        DynamicArray<std::string> arrStr(2);
        arrStr.set(0, "Привет");
        arrStr.set(1, "Мир");
        std::cout << "Массив string: " << arrStr << "\n\n";

        // 3. Расстояние между массивами
        DynamicArray<int> v1(3), v2(3);
        v1.set(0, 1); v1.set(1, 2); v1.set(2, 3);
        v2.set(0, 4); v2.set(1, 6); v2.set(2, 3);
        std::cout << "Расстояние между v1 и v2: " << distance(v1, v2) << "\n\n";

        // 4. Ошибка: разные размеры
        std::cout << "Попытка найти расстояние между v1 и массивом размера 2...\n";
        DynamicArray<int> v3(2);
        try {
            distance(v1, v3);
        } catch (const std::invalid_argument& e) {
            std::cout << "Поймано invalid_argument: " << e.what() << "\n";
        }

        // 5. Ошибка: нечисловой тип (bad_typeid)
        std::cout << "Попытка найти расстояние между строками...\n";
        try {
            distance(arrStr, arrStr);
        } catch (const std::bad_typeid& e) {
            std::cout << "Поймано bad_typeid: " << e.what() << "\n";
        }

    } catch (const std::exception& error) {
        std::cerr << "Неожиданная ошибка: " << error.what() << "\n";
        return 1;
    }
    return 0;
}