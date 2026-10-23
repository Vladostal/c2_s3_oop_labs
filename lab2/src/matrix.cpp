#include "matrix.hpp"

Matrix::Matrix() : rows_(0), cols_(0), data_(nullptr) {
}

Matrix::Matrix(std::size_t rows, std::size_t cols, double value) : rows_(rows), cols_(cols), data_(nullptr) {
    std::size_t count = rows_ * cols_;
    if (count == 0) {
        return;
    }
    data_ = new double[count];
    for (std::size_t i = 0; i < count; ++i) {
        data_[i] = value;
    }
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
    std::size_t count = rows_ * cols_;
    if (count == 0) {
        return;
    }
    data_ = new double[count];
    for (std::size_t i = 0; i < count; ++i) {
        data_[i] = other.data_[i];
    }
}

Matrix::Matrix(Matrix &&other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
}

Matrix &Matrix::operator=(Matrix other) {
    swap(other);
    return *this;
}

Matrix::~Matrix() {
    delete[] data_;
    data_ = nullptr;
}

void Matrix::swap(Matrix &other) noexcept {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(data_, other.data_);
}

std::size_t Matrix::rows() const {
    return rows_;
}

std::size_t Matrix::cols() const {
    return cols_;
}

double Matrix::get(std::size_t r, std::size_t c) const {
    if (r >= rows_ || c >= cols_) {
        return 0.0;
    }
    return data_[r * cols_ + c];
}

bool Matrix::set(std::size_t r, std::size_t c, double value) {
    if (r >= rows_ || c >= cols_) {
        return false;
    }
    data_[r * cols_ + c] = value;
    return true;
}

bool Matrix::add(const Matrix &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }
    std::size_t count = rows_ * cols_;
    for (std::size_t i = 0; i < count; ++i) {
        data_[i] += other.data_[i];
    }
    return true;
}

bool Matrix::mul(const Matrix &other) {
    if (cols_ != other.rows_) {
        return false;
    }
    Matrix result(rows_, other.cols_, 0.0);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < other.cols_; ++j) {
            double value = 0.0;
            for (std::size_t k = 0; k < cols_; ++k) {
                value += data_[i * cols_ + k] * other.data_[k * other.cols_ + j];
            }
            result.data_[i * other.cols_ + j] = value;
        }
    }
    swap(result);
    return true;
}

void Matrix::print(std::ostream &out) const {
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            out << data_[i * cols_ + j] << " ";
        }
        out << "\n";
    }
}

double Matrix::sum() const {
    double total = 0.0;
    std::size_t count = rows_ * cols_;
    for (std::size_t i = 0; i < count; ++i) {
        total += data_[i];
    }
    return total;
}
