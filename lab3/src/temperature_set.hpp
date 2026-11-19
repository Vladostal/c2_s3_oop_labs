#pragma once
#include <cstddef>
#include <iostream>

#include "temperature.hpp"

class TemperatureSet {
public:
    TemperatureSet();

    TemperatureSet(const TemperatureSet &other);

    TemperatureSet(TemperatureSet &&other) noexcept;

    TemperatureSet &operator=(const TemperatureSet &other);

    TemperatureSet &operator=(TemperatureSet &&other) noexcept;

    ~TemperatureSet();

    void swap(TemperatureSet &other) noexcept;

    bool add(const Temperature &t);

    bool remove(const Temperature &t);

    bool contains(const Temperature &t) const;

    bool operator()(const Temperature &t) const;

    std::size_t size() const;

    bool empty() const;

    TemperatureSet &operator+=(const Temperature &t);

    TemperatureSet &operator-=(const Temperature &t);

    TemperatureSet operator|(const TemperatureSet &other) const;

    TemperatureSet operator&(const TemperatureSet &other) const;

    TemperatureSet operator-(const TemperatureSet &other) const;

    bool operator==(const TemperatureSet &other) const;

    bool operator!=(const TemperatureSet &other) const;

    friend std::ostream &operator<<(std::ostream &out, const TemperatureSet &s);

private:
    void grow();

    Temperature *data_;
    std::size_t size_;
    std::size_t capacity_;
};
