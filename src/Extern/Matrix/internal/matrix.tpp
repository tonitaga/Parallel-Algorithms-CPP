#ifndef A3_PARALLELS_EXTERN_GRAPH_INTERNAL_MATRIX_TPP_
#define A3_PARALLELS_EXTERN_GRAPH_INTERNAL_MATRIX_TPP_

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>

#include "inf.h"
#include "matrix.h"

namespace s21 {
    template<typename T>
    Matrix<T>::Matrix(size_type rows, size_type cols, value_type fill)
            : rows_(rows), cols_(cols), data_(rows_ * cols_, fill) {}

    template<typename T>
    Matrix<T>::Matrix(size_type square, value_type fill)
            : Matrix(square, square, fill) {}

    template<typename T>
    Matrix<T>::Matrix(const Matrix &other) {
        if (this == &other) return;
        *this = Matrix(other.rows_, other.cols_, T{});
        for (size_type i = 0; i != data_.size(); ++i)
            if (other.data_[i] != kInf<T>) data_[i] = other.data_[i];
    }

    template<typename T>
    Matrix<T>::Matrix(const std::vector<std::vector<value_type>> &vector_matrix)
            : Matrix(vector_matrix.size(),
                     vector_matrix.empty() ? 0 : vector_matrix[0].size(), T{}) {
        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                (*this)(row, col) = vector_matrix[row][col];
    }

    template<typename T>
    Matrix<T> &Matrix<T>::operator=(const Matrix &other) {
        if (this == &other) return *this;
        *this = Matrix(other.rows_, other.cols_, T{});
        for (size_type i = 0; i != data_.size(); ++i)
            if (other.data_[i] != kInf<T>) data_[i] = other.data_[i];
        return *this;
    }

    template<typename T>
    Matrix<T> &Matrix<T>::operator=(
            const std::vector<std::vector<value_type>> &vector_matrix) {
        Matrix<T> matrix(vector_matrix);
        *this = std::move(matrix);
        return *this;
    }

    template<typename T>
    bool Matrix<T>::operator==(const Matrix &other) const {
        return rows_ == other.getRows() and cols_ == other.getCols() and data_ =
                       other.data_;
    }

    template<typename T>
    typename Matrix<T>::size_type Matrix<T>::getElementCount() const noexcept {
        return rows_ * cols_;
    }

    template<typename T>
    typename Matrix<T>::size_type Matrix<T>::getCols() const noexcept {
        return cols_;
    }

    template<typename T>
    typename Matrix<T>::size_type Matrix<T>::getRows() const noexcept {
        return rows_;
    }

    template<typename T>
    bool Matrix<T>::isSquare() const noexcept {
        return rows_ == cols_;
    }

    template<typename T>
    typename Matrix<T>::reference Matrix<T>::operator()(size_type row,
                                                        size_type col) {
        return data_[row * cols_ + col];
    }

    template<typename T>
    typename Matrix<T>::const_reference Matrix<T>::operator()(size_type row,
                                                              size_type col) const {
        return data_[row * cols_ + col];
    }

    template<typename T>
    typename Matrix<T>::const_reference Matrix<T>::getElement(size_type row,
                                                              size_type col) const {
        return data_[row * cols_ + col];
    }

    template<typename T>
    void Matrix<T>::setRows(size_type rows) {
        if (rows == rows_) return;
        rows_ = rows;
        data_.resize(rows_ * cols_);
    }

    template<typename T>
    void Matrix<T>::setCols(size_type cols) {
        if (cols == cols_) return;
        cols_ = cols;
        data_.resize(rows_ * cols_);
    }

    template<typename T>
    void Matrix<T>::Fill(value_type fill) {
        std::fill(data_.begin(), data_.end(), fill);
    }

    template<typename T>
    void Matrix<T>::FillRandomly(value_type left_border, value_type right_border) {
        if constexpr (std::is_floating_point_v<value_type>) {
            std::uniform_real_distribution dist(left_border, right_border);
            std::default_random_engine re(
                    std::chrono::system_clock::now().time_since_epoch().count());
            std::generate(data_.begin(), data_.end(),
                          [&dist, &re]() { return dist(re); });
        } else {
            std::uniform_int_distribution<value_type> dist(left_border, right_border);
            std::default_random_engine re(
                    std::chrono::system_clock::now().time_since_epoch().count());
            std::generate(data_.begin(), data_.end(),
                          [&dist, &re]() { return dist(re); });
        }
    }

    template<typename T>
    Matrix<T> Matrix<T>::RandomAdjacencyMatrix(std::size_t square, T left_border,
                                               T right_border) {
        Matrix<T> m(square);
        m.FillRandomly(left_border, right_border);

        for (size_type row = 0; row != m.getRows(); ++row)
            for (size_type col = 0; col != row; ++col) m(row, col) = m(col, row);

        for (size_type row = 0; row != m.getRows(); ++row)
            for (size_type col = 0; col != m.getCols(); ++col)
                if (row == col) m(row, col) = value_type{};

        return m;
    }

    template<typename T>
    std::vector<std::vector<T>> Matrix<T>::toVectorMatrix() const {
        std::vector<std::vector<T>> vector_matrix(rows_, std::vector<T>(cols_));

        for (size_type row = 0; row != rows_; ++row)
            for (size_type col = 0; col != cols_; ++col)
                vector_matrix[row][col] = getElement(row, col);

        return vector_matrix;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &rhs) {
        for (std::size_t row = 0, rows = rhs.getRows(); row != rows; ++row) {
            for (std::size_t col = 0, cols = rhs.getCols(); col != cols; ++col) {
                if (rhs(row, col) == kInf<T>)
                    out << T{} << ' ';
                else
                    out << std::setprecision(3) << rhs(row, col) << ' ';
            }
            if (row != rows - 1) out << std::endl;
        }

        return out;
    }
}  // namespace s21

#endif  // A3_PARALLELS_EXTERN_GRAPH_INTERNAL_MATRIX_TPP_
