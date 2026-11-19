#include <ostream>
#include <cmath>

#include "temperature.hpp"

Temperature::Temperature() : value_(0.0), unit_(Unit::Kelvin) {
}

Temperature::Temperature(double value, Unit unit) : value_(value), unit_(unit) {
}

double Temperature::kelvin() const {
    if (unit_ == Unit::Celsius) {
        return value_ + 273.15;
    }
    if (unit_ == Unit::Fahrenheit) {
        return (value_ - 32.0) * 5.0 / 9.0 + 273.15;
    }
    return value_;
}

bool Temperature::is_valid() const {
    return kelvin() >= 0.0;
}

bool Temperature::operator==(const Temperature &other) const {
    return std::fabs(kelvin() - other.kelvin()) < 1e-9;
}

std::ostream &operator<<(std::ostream &out, const Temperature &t) {
    out << t.value_;
    if (t.unit_ == Unit::Celsius) {
        out << " C";
    } else if (t.unit_ == Unit::Fahrenheit) {
        out << " F";
    } else {
        out << " K";
    }
    return out;
}
