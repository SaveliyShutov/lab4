# Лабораторная работа: Класс Money

## 1. Условие

**Типы полей:** `unsigned int rubles_`, `short kopeks_`.

### Требуется реализовать:

- **Вычитание** переменной типа `Money` (результат не может быть отрицательным; возвращает `Money`).
- **Унарные операции:** `++` (добавление 1 копейки) и `--` (вычитание 1 копейки).
- **Приведение типов:**
  - `operator unsigned int()` — неявное: количество рублей (копейки отбрасываются).
  - `explicit operator double()` — явное: дробная часть в рублях (`kopeks / 100.0`), результат < 1.
- **Бинарные операции:**
  - `Money operator+(const Money&)` и `Money operator+(unsigned int)` (результат — `Money`).
  - `Money operator-(const Money&)` и `Money operator-(unsigned int)` (результат — `Money`, неотрицательный).
- **Проверка входных данных:** рубли >= 0, копейки >= 0 (копейки могут быть >= 100 — нормализация выполняется классом).

---

## 2. Структура проекта (файлы)

- `Money.h` — заголовочный файл с объявлением класса `Money`.
- `Money.cpp` — реализация класса (конструкторы, Normalize, перегрузки операторов, приватные вспомогательные функции).
- `main.cpp` — интерфейс ввода/вывода, функция `ReadMoney()` и демонстрация всех операций в `main()`.

---

## 3. Описание класса Money

### Поля (private)

```cpp
unsigned int rubles_;
short kopeks_;
Конструкторы (минимум 3)
cpp
Copy code
Money(); // по умолчанию: 0 руб. 0 коп.
Money(unsigned int rubles, short int kopeks); // инициализация по рублям и копейкам
explicit Money(unsigned long long totalKopeks); // инициализация из общего числа копеек
Вспомогательные (private)
cpp
Copy code
void Normalize(); // нормализация копеек
unsigned long long ToTotalKopeks() const; // общее количество копеек
static Money FromTotalKopeks(unsigned long long total); // фабричный метод
Методы (public)
cpp
Copy code
unsigned int GetRubles() const;
short GetKopeks() const;
Перегрузки операторов
Вывод:

cpp
Copy code
friend std::ostream& operator<<(std::ostream& os, const Money& m); // формат: X руб YY коп
Унарные:

cpp
Copy code
Money& operator++(); // префикс ++
Money operator++(int); // постфикс ++
Money& operator--(); // префикс --
Money operator--(int); // постфикс --
Бинарные:

cpp
Copy code
Money operator+(const Money& other) const;
Money operator+(unsigned int rubles) const;
Money operator-(const Money& other) const; // результат >= 0
Money operator-(unsigned int rubles) const; // результат >= 0
Приведение типов:

cpp
Copy code
operator unsigned int() const; // неявное — рубли
explicit operator double() const; // явное — дробная часть < 1
4. Ввод данных: ReadMoney()
cpp
Copy code
Money ReadMoney(const std::string& prompt);
Поведение:

Ввод: две целочисленных величины через пробел — рубли и копейки.

Валидация:

рубли >= 0

копейки >= 0 (верхнего ограничения нет — класс нормализует)

После корректного ввода возвращает Money(rubles, kopeks).

Поток очищается (ignore) после успешного ввода.

Пример:

makefile
Copy code
Введите сумму (рубли и копейки через пробел): 5 250
Результат: 7 руб 50 коп
5. Демонстрация использования (main.cpp)
Ввод, вывод и вычитание:
text
Copy code
Введите первую сумму (рубли и копейки через пробел): 5 250
Первая сумма: 7 руб 50 коп
Унарные операции:
cpp
Copy code
++a;        // +1 копейка
a++;        // постфикс
--a;        // -1 копейка (не ниже 0)
Приведения типов:
cpp
Copy code
unsigned int rub = a;             // implicit, ровно целые рубли
double frac = static_cast<double>(a); // explicit, дробная часть < 1
6. Примеры запуска и ожидаемый вывод
Пример 1 — проверка нормализации копеек:
makefile
Copy code
Введите сумму (рубли и копейки через пробел): 3 250
Результат: 5 руб 50 коп
Пример 2 — вычитание, результат неотрицательный:
makefile
Copy code
m1: 10 руб 00 коп
m2: 12 руб 30 коп
m1 - m2 = 0 руб 00 коп
Пример 3 — ++/--:
rust
Copy code
a = 0 руб 00 коп
++a -> 0 руб 01 коп
a++ -> 0 руб 02 коп
--a -> 0 руб 01 коп
a-- -> 0 руб 00 коп
Пример 4 — приведения:
cpp
Copy code
a = 15 руб 75 коп
unsigned int r = a;             // r == 15
double frac = static_cast<double>(a); // frac == 0.75
