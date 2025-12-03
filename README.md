1. Условие

Типы полей: unsigned int rubles_, short kopeks_.

Реализовать вычитание переменной типа Money (результат не может быть отрицательным; возвращаем Money).

Унарные операции: ++ (добавление 1 копейки) и -- (вычитание 1 копейки).

Приведение типов:

operator unsigned int() — неявное: количество рублей (копейки отбрасываются).

explicit operator double() — явное: дробная часть в рублях (копейки/100.0), результат < 1.

Бинарные операции:

Money operator+(const Money&) и Money operator+(unsigned int) (результат — Money).

Money operator-(const Money&) и Money operator-(unsigned int) (результат — Money, неотрицательный).

Проверка входных данных: рубли >= 0, копейки >= 0 (копейки можно вводить >= 100 — нормализация выполняется классом).

2. Структура проекта (файлы)

Money.h — заголовочный файл с объявлением класса Money.

Money.cpp — реализация класса (конструкторы, Normalize, все перегрузки операторов, приватные вспомогательные функции).

main.cpp — интерфейс ввода/вывода, функция ReadMoney() и демонстрация всех операций в main().

3. Описание класса Money
Поля (private)
unsigned int rubles_;
short kopeks_;

Конструкторы (минимум 3)

Money() — конструктор по умолчанию, устанавливает 0 руб. 0 коп.

Money(unsigned int rubles, short int kopeks) — инициализация по рублям и копейкам; вызывает Normalize().

explicit Money(unsigned long long totalKopeks) — инициализация из общего числа копеек; explicit требует явного вызова (static_cast<Money>(...)), затем Normalize().

Вспомогательные (private)

void Normalize() — переводит поля в корректное состояние: копейки в диапазон 0..99, лишние копейки добавляются к рублям; если суммарно ≤ 0 — выставляет 0/0.

unsigned long long ToTotalKopeks() const — возвращает общее количество копеек как unsigned long long.

static Money FromTotalKopeks(unsigned long long total) — фабричный метод, создаёт Money из общего числа копеек.

Методы (public)
unsigned int GetRubles() const;
short GetKopeks() const;

Перегрузки операторов

friend std::ostream& operator<<(std::ostream& os, const Money& m); — вывод в формате X руб YY коп.

Унарные:

Money& operator++(); // префикс ++ (добавляет 1 копейку)

Money operator++(int); // постфикс ++

Money& operator--(); // префикс -- (вычитает 1 копейку, не ниже 0)

Money operator--(int); // постфикс --

Бинарные:

Money operator+(const Money& other) const;

Money operator+(unsigned int rubles) const;

Money operator-(const Money& other) const; // результат >= 0

Money operator-(unsigned int rubles) const; // результат >= 0

Приведение типов:

operator unsigned int() const; // неявное — возвращает только рубли

explicit operator double() const; // явное — дробная часть рубля (kopeks / 100.0)

4. Ввод данных: ReadMoney() (поведение)

Ввод: две целочисленных величины через пробел — рубли и копейки.

Валидация:

рубли должен быть >= 0.

копейки должен быть >= 0 (верхнего ограничения нет — класс нормализует).

После корректного ввода ReadMoney возвращает Money(rubles, kopeks).

Поток очищается (ignore) после успешного ввода.

Пример сигнатуры:

Money ReadMoney(const std::string& prompt);

5. Примеры использования и демонстрация (фрагменты main.cpp)

Демонстрация ввода, вывода и вычитания:

Введите первую сумму (рубли и копейки через пробел): 5 250
Первая сумма: 7 руб 50 коп


(т.е. введено 5 руб 250 коп => нормализовано в 7 руб 50 коп.)

Демонстрация ++/-- и приведений:

++a;        // +1 копейка
a++;        // постфикс
--a;        // -1 копейка (не уйдёт ниже 0)
unsigned int rub = a; // implicit, ровно целые рубли
double frac = static_cast<double>(a); // explicit, дробная часть < 1

6. Примеры запуска и ожидаемый вывод

Сборка:

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp Money.cpp -o money


Пример 1 — проверка нормализации копеек:

Введите сумму (рубли и копейки через пробел): 3 250
Результат: 5 руб 50 коп


Пример 2 — вычитание, результат неотрицательный:

m1: 10 руб 00 коп
m2: 12 руб 30 коп
m1 - m2 = 0 руб 00 коп


Пример 3 — ++/--:

a = 0 руб 00 коп
++a -> 0 руб 01 коп
a++ -> 0 руб 02 коп
--a -> 0 руб 01 коп
a-- -> 0 руб 00 коп


Пример 4 — приведения:

a = 15 руб 75 коп
unsigned int r = a;             // r == 15
double frac = static_cast<double>(a); // frac == 0.75
