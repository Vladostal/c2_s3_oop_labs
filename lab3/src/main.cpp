#include <iostream>

#include "temperature_set.hpp"

int main() {
    TemperatureSet a;
    a.add(Temperature(0.0, Unit::Celsius));
    a.add(Temperature(32.0, Unit::Fahrenheit));
    a.add(Temperature(100.0, Unit::Celsius));

    TemperatureSet b;
    b.add(Temperature(373.15, Unit::Kelvin));
    b.add(Temperature(-40.0, Unit::Celsius));

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a | b = " << (a | b) << std::endl;
    std::cout << "a & b = " << (a & b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    return 0;
}
