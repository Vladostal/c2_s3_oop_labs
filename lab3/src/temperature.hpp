#pragma once
#include <iostream>

enum class Unit {
    Celsius,
    Fahrenheit,
    Kelvin
};

class Temperature {
public:
    Temperature();

    Temperature(double value, Unit unit);

    double kelvin() const;

    bool is_valid() const;

    bool operator==(const Temperature &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Temperature &t);

private:
    double value_;
    Unit unit_;
};
