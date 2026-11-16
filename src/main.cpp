#include "../include/DynamicArray.h"
#include <iostream>

int main() {
    try {
        std::cout << "Часть 4: Операторы \n\n";

        DynamicArray<int> a(3);
        DynamicArray<int> b(3);

        // 1. Демонстрация оператора []
        std::cout << "1. Оператор []:\n";
        a[0] = 10; 
        a[1] = 20;
        a[2] = 30;
        std::cout << "Массив a: " << a << "\n";
        std::cout << "Чтение a[1]: " << a[1] << "\n";

        b[0] = 10;
        b[1] = 20;
        b[2] = 30;

        // 2. Демонстрация == и !=
        std::cout << "\n2. Операторы сравнения:\n";
        std::cout << "a == b: " << (a == b ? "Истина" : "Ложь") << "\n";
        b[0] = 99;
        std::cout << "Изменили b[0]. Теперь a == b: " << (a == b ? "Истина" : "Ложь") << "\n";
        std::cout << "a != b: " << (a != b ? "Истина" : "Ложь") << "\n";

        // 3. Демонстрация += и -=
        std::cout << "\n3. Составные операторы:\n";
        DynamicArray<int> c(4);
        c[0] = 1; c[1] = 2; c[2] = 3; c[3] = 4;
        
        std::cout << "Массив c до: " << c << "\n";
        c += 5; 
        std::cout << "c += 5: " << c << "\n";
        
        c -= 1; 
        std::cout << "c -= 1: " << c << "\n";

        DynamicArray<int> d(2);
        d[0] = 10; d[1] = 10;
        c += d;
        std::cout << "c += d (d размера 2): " << c << "\n";

        // 4. Демонстрация итераторов
        std::cout << "\n4. Итераторы (range-based for):\n";
        std::cout << "Умножаем все элементы c на 2 через цикл for...\n";
        for (auto& x : c) {
            x *= 2;
        }
        std::cout << "Массив c после: " << c << "\n";

        // Проверка выброса исключения при выходе за границы
        try {
            std::cout << "\nПопытка a[99] = 5...\n";
            a[99] = 5;
        } catch (const std::out_of_range& e) {
            std::cout << "Поймано исключение: " << e.what() << "\n";
        }

    } catch (const std::exception& error) {
        std::cerr << "Неожиданная ошибка: " << error.what() << "\n";
        return 1;
    }
    return 0;
}