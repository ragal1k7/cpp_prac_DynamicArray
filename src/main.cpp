#include "../include/DynamicArray.h"
#include <iostream>
#include <utility> // для std::move

// Функция, принимающая массив по значению (для демонстрации)
void processArrayByValue(DynamicArray<int> arr) {
    std::cout << "  [Внутри функции] Размер полученного массива: " << arr.size() << "\n";
}

int main() {
    try {
        std::cout << "=== Часть 5: Правило пяти ===\n\n";

        // Задание 1: Копирующее присваивание 
        std::cout << "1. Оператор присваивания копированием:\n";
        DynamicArray<int> a(3);
        a[0] = 1; a[1] = 2; a[2] = 3;
        
        DynamicArray<int> b(5);
        b = a;
        std::cout << "Массив a: " << a << "\n";
        std::cout << "Массив b (скопирован из a): " << b << "\n\n";

        // Задание 4: Демонстрация копирования vs Перемещения 
        std::cout << "2. Передача по значению (Копирование):\n";
        std::cout << "Копируем массив a в функцию...\n";
        processArrayByValue(a); 
        
        std::cout << "\n3. Передача по значению (Перемещение / Move):\n";
        std::cout << "Перемещаем массив b в функцию с помощью std::move...\n";
        processArrayByValue(std::move(b)); 
        
        std::cout << "Массив b после move: " << b << " (размер: " << b.size() << ")\n\n";

        std::cout << "4. Проверка самоприсваивания:\n";
        DynamicArray<int> c(2);
        c[0] = 10; c[1] = 20;
        c = c; 
        std::cout << "Массив c после c = c: " << c << "\n";

    } catch (const std::exception& error) {
        std::cerr << "Неожиданная ошибка: " << error.what() << "\n";
        return 1;
    }
    return 0;
}