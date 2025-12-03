#include <iostream>
#include "Money.h"

Money ReadMoney(const std::string& prompt) {
    long long r;
    short k;
    while (true) {
        std::cout << prompt;
        if (std::cin >> r >> k) {
            if (r < 0 || k < 0) {
                std::cout << "Рубли и копейки не могут быть отрицательными! Введите снова.\n";
                continue;
            }
            break;
        } else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка ввода! Введите два числа через пробел.\n";
        }
    }
    return Money(static_cast<unsigned int>(r), k);
}

int main() {
    std::cout << "Задание 1: Money класс, вычитание\n";
    Money m1 = ReadMoney("Введите первую сумму (рубли и копейки через пробел): ");
    Money m2 = ReadMoney("Введите вторую сумму (рубли и копейки через пробел): ");

    std::cout << "Первая сумма: " << m1 << "\n";
    std::cout << "Вторая сумма: " << m2 << "\n";

    Money diff = m1 - m2;
    std::cout << "Результат вычитания m1 - m2: " << diff << "\n\n";

    std::cout << "Задание 2: Money с перегруженными операциями\n";
    Money a = ReadMoney("Введите первую сумму (рубли и копейки через пробел): ");
    Money b = ReadMoney("Введите вторую сумму (рубли и копейки через пробел): ");

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";

    ++a;
    std::cout << "После ++a: " << a << "\n";
    a++;
    std::cout << "После a++: " << a << "\n";
    --a;
    std::cout << "После --a: " << a << "\n";
    a--;
    std::cout << "После a--: " << a << "\n";

    unsigned int rub = a;
    double fraction = static_cast<double>(a);
    std::cout << "Рубли (неявное): " << rub << "\n";
    std::cout << "Дробная часть рубля (явное): " << fraction << "\n";

    Money sum = a + b;
    Money sumWithUInt = a + 100u;
    Money diffAB = a - b;

    std::cout << "a + b: " << sum << "\n";
    std::cout << "a + 100 руб: " << sumWithUInt << "\n";
    std::cout << "a - b: " << diffAB << "\n";

    return 0;
}
