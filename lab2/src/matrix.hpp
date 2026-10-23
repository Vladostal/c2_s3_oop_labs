#pragma once
#include <iostream>

class Matrix {
public:
    Matrix();

    Matrix(std::size_t rows, std::size_t cols, double value);

    Matrix(const Matrix &other);

    Matrix(Matrix &&other) noexcept;

    Matrix &operator=(Matrix other);

    ~Matrix();

    void swap(Matrix &other) noexcept;

    std::size_t rows() const;

    std::size_t cols() const;

    double get(std::size_t r, std::size_t c) const;

    bool set(std::size_t r, std::size_t c, double value);

    bool add(const Matrix &other);

    bool mul(const Matrix &other);

    void print(std::ostream &out) const;

    double sum() const;

private:
    std::size_t rows_;
    std::size_t cols_;
    double *data_;
};
