#ifndef MONEY_H
#define MONEY_H

#include <iostream>

class Money {
public:
  Money();
  Money(unsigned int rubles, short int kopeks);
  explicit Money(unsigned long long totalKopeks);

  unsigned int GetRubles() const;
  short GetKopeks() const;

  Money operator-(const Money &other) const;

  Money &operator++();   // префикс
  Money operator++(int); // постфикс
  Money &operator--();   // префикс
  Money operator--(int); // постфикс
  Money operator+(const Money &other) const;
  Money operator+(unsigned int rubles) const;
  explicit operator double() const;
  operator unsigned int() const;

  friend std::ostream &operator<<(std::ostream &os, const Money &m);

private:
  unsigned int rubles_;
  short kopeks_;

  void Normalize();
  unsigned long long ToTotalKopeks() const;
  static Money FromTotalKopeks(unsigned long long total);
};

#endif
