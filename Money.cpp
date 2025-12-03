#include "Money.h"

Money::Money() : rubles_(0), kopeks_(0) {}

Money::Money(unsigned int rubles, short int kopeks)
    : rubles_(rubles), kopeks_(kopeks) {
    Normalize();
}

Money::Money(unsigned long long totalKopeks) {
    rubles_ = static_cast<unsigned int>(totalKopeks / 100);
    kopeks_ = static_cast<short>(totalKopeks % 100);
    Normalize();
}

unsigned int Money::GetRubles() const { return rubles_; }
short Money::GetKopeks() const { return kopeks_; }

Money Money::operator-(const Money& other) const {
    long long a = static_cast<long long>(rubles_) * 100 + kopeks_;
    long long b = static_cast<long long>(other.rubles_) * 100 + other.kopeks_;
    if (a <= b) return Money(0,0);
    return FromTotalKopeks(a - b);
}

Money& Money::operator++() {
    ++kopeks_;
    Normalize();
    return *this;
}

Money Money::operator++(int) {
    Money temp = *this;
    ++*this;
    return temp;
}

Money& Money::operator--() {
    long long total = static_cast<long long>(rubles_) * 100 + kopeks_;
    if (total > 0) --total;
    rubles_ = static_cast<unsigned int>(total / 100);
    kopeks_ = static_cast<short>(total % 100);
    return *this;
}

Money Money::operator--(int) {
    Money temp = *this;
    --*this;
    return temp;
}

Money Money::operator+(const Money& other) const {
    return FromTotalKopeks(ToTotalKopeks() + other.ToTotalKopeks());
}

Money Money::operator+(unsigned int rubles) const {
    return Money(rubles_ + rubles, kopeks_);
}

Money::operator unsigned int() const {
    return rubles_;
}

Money::operator double() const {
    return static_cast<double>(kopeks_) / 100.0;
}

std::ostream& operator<<(std::ostream& os, const Money& m) {
    os << m.rubles_ << " руб " << (m.kopeks_ < 10 ? "0" : "") << m.kopeks_ << " коп";
    return os;
}

void Money::Normalize() {
    if (kopeks_ >= 100) {
        rubles_ += kopeks_ / 100;
        kopeks_ %= 100;
    }
}

unsigned long long Money::ToTotalKopeks() const {
    return static_cast<unsigned long long>(rubles_) * 100 + kopeks_;
}

Money Money::FromTotalKopeks(unsigned long long total) {
    unsigned int r = static_cast<unsigned int>(total / 100);
    short k = static_cast<short>(total % 100);
    return Money(r, k);
}
