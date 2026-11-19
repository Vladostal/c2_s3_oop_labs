#include <ostream>
#include <utility>

#include "temperature_set.hpp"

TemperatureSet::TemperatureSet() : data_(nullptr), size_(0), capacity_(0) {
}

TemperatureSet::TemperatureSet(const TemperatureSet &other)
    : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ == 0) {
        return;
    }
    data_ = new Temperature[capacity_];
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

TemperatureSet::TemperatureSet(TemperatureSet &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

TemperatureSet &TemperatureSet::operator=(const TemperatureSet &other) {
    if (this != &other) {
        TemperatureSet tmp(other);
        swap(tmp);
    }
    return *this;
}

TemperatureSet &TemperatureSet::operator=(TemperatureSet &&other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

TemperatureSet::~TemperatureSet() {
    delete[] data_;
    data_ = nullptr;
}

void TemperatureSet::swap(TemperatureSet &other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void TemperatureSet::grow() {
    std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    Temperature *new_data = new Temperature[new_capacity];
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

bool TemperatureSet::add(const Temperature &t) {
    if (!t.is_valid() || contains(t)) {
        return false;
    }
    if (size_ == capacity_) {
        grow();
    }
    data_[size_] = t;
    ++size_;
    return true;
}

bool TemperatureSet::remove(const Temperature &t) {
    for (std::size_t i = 0; i < size_; ++i) {
        if (data_[i] == t) {
            for (std::size_t j = i; j + 1 < size_; ++j) {
                data_[j] = data_[j + 1];
            }
            --size_;
            return true;
        }
    }
    return false;
}

bool TemperatureSet::contains(const Temperature &t) const {
    for (std::size_t i = 0; i < size_; ++i) {
        if (data_[i] == t) {
            return true;
        }
    }
    return false;
}

bool TemperatureSet::operator()(const Temperature &t) const {
    return contains(t);
}

std::size_t TemperatureSet::size() const {
    return size_;
}

bool TemperatureSet::empty() const {
    return size_ == 0;
}

TemperatureSet &TemperatureSet::operator+=(const Temperature &t) {
    add(t);
    return *this;
}

TemperatureSet &TemperatureSet::operator-=(const Temperature &t) {
    remove(t);
    return *this;
}

TemperatureSet TemperatureSet::operator|(const TemperatureSet &other) const {
    TemperatureSet result(*this);
    for (std::size_t i = 0; i < other.size_; ++i) {
        result.add(other.data_[i]);
    }
    return result;
}

TemperatureSet TemperatureSet::operator&(const TemperatureSet &other) const {
    TemperatureSet result;
    for (std::size_t i = 0; i < size_; ++i) {
        if (other.contains(data_[i])) {
            result.add(data_[i]);
        }
    }
    return result;
}

TemperatureSet TemperatureSet::operator-(const TemperatureSet &other) const {
    TemperatureSet result;
    for (std::size_t i = 0; i < size_; ++i) {
        if (!other.contains(data_[i])) {
            result.add(data_[i]);
        }
    }
    return result;
}

bool TemperatureSet::operator==(const TemperatureSet &other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (std::size_t i = 0; i < size_; ++i) {
        if (!other.contains(data_[i])) {
            return false;
        }
    }
    return true;
}

bool TemperatureSet::operator!=(const TemperatureSet &other) const {
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &out, const TemperatureSet &s) {
    out << "{ ";
    for (std::size_t i = 0; i < s.size_; ++i) {
        if (i > 0) {
            out << ", ";
        }
        out << s.data_[i];
    }
    if (s.size_ > 0) {
        out << " ";
    }
    out << "}";
    return out;
}
