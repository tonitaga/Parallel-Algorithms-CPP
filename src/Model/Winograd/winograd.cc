#include "winograd.h"

#include <omp.h>

#include <random>

namespace s21 {
    Winograd::Winograd(const Matrix<double> &m1, const Matrix<double> &m2)
            : matrix1_(m1), matrix2_(m2) {};

    Winograd::Winograd(Matrix<double> &&m1, Matrix<double> &&m2) noexcept
            : matrix1_(std::move(m1)), matrix2_(std::move(m2)) {}

    Winograd::Winograd(std::size_t rows1, std::size_t cols1, std::size_t rows2,
                       std::size_t cols2)
            : matrix1_(rows1, cols1, {}), matrix2_(rows2, cols2, {}) {
        FillMatricesRandomly();
    };

    Matrix<double> Winograd::MultiplyNaive() const {
        Matrix<double> correct_answer;

        try {
            if (MatrixesIsInValid()) {
                return {};
            }

            const std::size_t kRows = matrix1_.getRows(), kCols = matrix2_.getCols();
            Matrix<double> result(kRows, kCols, 0.0);

            for (std::size_t row = 0; row != kRows; ++row)
                for (std::size_t col = 0; col != kCols; ++col)
                    for (std::size_t k = 0; k != matrix1_.getCols(); ++k)
                        result(row, col) += matrix1_(row, k) * matrix2_(k, col);

            correct_answer = std::move(result);

        } catch (std::exception &e) {
            std::cerr << "Caught exception. Info: " << e.what() << std::endl;
            correct_answer = Matrix<double>{};
        }

        return correct_answer;
    }

    Matrix<double> Winograd::MultiplySimple() const {
        Matrix<double> correct_answer;

        try {
            if (MatrixesIsInValid()) {
                return {};
            }

            auto row_factor = ComputeRowFactorSeq();
            auto col_factor = ComputeColFactorSeq();

            auto result = ComputeMultiplicationMainSeq(row_factor, col_factor);

            if (matrix1_.getRows() % 2 != 0) ComputeAdditionSeq(result);

            correct_answer = std::move(result);

        } catch (std::exception &e) {
            std::cerr << "Caught exception. Info: " << e.what() << std::endl;
            correct_answer = Matrix<double>{};
        }

        return correct_answer;
    }

    Matrix<double> Winograd::MultiplyUsingThreads(std::size_t threads_count) const {
        Matrix<double> correct_answer;

        try {
            if (MatrixesIsInValid()) {
                return {};
            }

            omp_set_num_threads(threads_count);

            auto row_factor = ComputeRowFactorPar();
            auto col_factor = ComputeColFactorPar();

            auto result = ComputeMultiplicationMainPar(row_factor, col_factor);

            if (matrix1_.getRows() % 2 != 0) ComputeAdditionPar(result);

            correct_answer = std::move(result);

        } catch (std::exception &e) {
            std::cerr << "Caught exception. Info: " << e.what() << std::endl;
            correct_answer = Matrix<double>{};
        }

        return correct_answer;
    }

    Matrix<double> Winograd::MultiplyUsingPipelineParallelism(
            std::size_t threads_count) const {
        Matrix<double> correct_answer;

        try {
            if (MatrixesIsInValid()) {
                return {};
            }

            omp_set_num_threads(threads_count);

            std::vector<double> row_factor, col_factor;
            std::thread t1([&]() { row_factor = ComputeRowFactorPar(); });

            std::thread t2([&]() { col_factor = ComputeColFactorPar(); });

            t1.join(), t2.join();

            Matrix<double> result;
            result = ComputeMultiplicationMainPar(row_factor, col_factor);

            if (matrix1_.getRows() % 2 != 0) ComputeAdditionPar(result);

            correct_answer = std::move(result);

        } catch (std::exception &e) {
            std::cerr << "Caught exception. Info: " << e.what() << std::endl;
            correct_answer = Matrix<double>{};
        }

        return correct_answer;
    }

    void Winograd::setMatrices(const Matrix<double> &m1, const Matrix<double> &m2) {
        matrix1_ = m1;
        matrix2_ = m2;
    }

    void Winograd::setMatrices(Matrix<double> &&m1, Matrix<double> &&m2) noexcept {
        matrix1_ = std::move(m1);
        matrix2_ = std::move(m2);
    }

    void Winograd::setMatrices(std::size_t rows1, std::size_t cols1,
                               std::size_t rows2, std::size_t cols2) {
        matrix1_ = {rows1, cols1, {}};
        matrix2_ = {rows2, cols2, {}};
        FillMatricesRandomly();
    }

    void Winograd::FillMatricesRandomly() {
        matrix1_.FillRandomly(-10.0, 10.0);
        matrix2_.FillRandomly(-10.0, 10.0);
    }

    std::vector<double> Winograd::ComputeRowFactorPar() const {
        const std::size_t kSize = matrix1_.getRows();
        std::vector<double> row_factor(kSize);

#pragma omp parallel for
        for (std::size_t row = 0; row != kSize; ++row) {
            for (std::size_t j = 0, n_2 = kSize / 2; j < n_2; ++j)
                row_factor[row] += matrix1_(row, 2 * j) * matrix1_(row, 2 * j + 1);
        }

        return row_factor;
    }

    std::vector<double> Winograd::ComputeColFactorPar() const {
        const std::size_t kSize = matrix2_.getCols();
        std::vector<double> col_factor(kSize);

#pragma omp parallel for
        for (std::size_t col = 0; col != kSize; ++col) {
            for (std::size_t j = 0, n_2 = kSize / 2; j < n_2; ++j)
                col_factor[col] += matrix2_(2 * j, col) * matrix2_(2 * j + 1, col);
        }

        return col_factor;
    }

    std::vector<double> Winograd::ComputeRowFactorSeq() const {
        const std::size_t kSize = matrix1_.getRows();
        std::vector<double> row_factor(kSize);

        for (std::size_t row = 0; row != kSize; ++row) {
            for (std::size_t j = 0, n_2 = kSize / 2; j < n_2; ++j)
                row_factor[row] += matrix1_(row, 2 * j) * matrix1_(row, 2 * j + 1);
        }

        return row_factor;
    }

    std::vector<double> Winograd::ComputeColFactorSeq() const {
        const std::size_t kSize = matrix2_.getCols();
        std::vector<double> col_factor(kSize);

        for (std::size_t col = 0; col != kSize; ++col) {
            for (std::size_t j = 0, n_2 = kSize / 2; j < n_2; ++j)
                col_factor[col] += matrix2_(2 * j, col) * matrix2_(2 * j + 1, col);
        }

        return col_factor;
    }

    Matrix<double> Winograd::ComputeMultiplicationMainPar(
            const std::vector<double> &row_factor,
            const std::vector<double> &col_factor) const {
        std::size_t n = matrix1_.getRows(), m = matrix2_.getCols();

        Matrix<double> result(n, m, 0);

#pragma omp parallel for
        for (std::size_t row = 0; row < n; ++row) {
            for (std::size_t col = 0; col < m; ++col) {
                result(row, col) = -row_factor[row] - col_factor[col];

                for (std::size_t k = 0, n_2 = n / 2; k != n_2; ++k) {
                    result(row, col) += (matrix1_(row, 2 * k) + matrix2_(2 * k + 1, col)) *
                                        (matrix1_(row, 2 * k + 1) + matrix2_(2 * k, col));
                }
            }
        }

        return result;
    }

    Matrix<double> Winograd::ComputeMultiplicationMainSeq(
            const std::vector<double> &row_factor,
            const std::vector<double> &col_factor) const {
        std::size_t n = matrix1_.getRows(), m = matrix2_.getCols();

        Matrix<double> result(n, m, 0);
        for (std::size_t row = 0; row < n; ++row) {
            for (std::size_t col = 0; col < m; ++col) {
                result(row, col) = -row_factor[row] - col_factor[col];

                for (std::size_t k = 0, n_2 = n / 2; k != n_2; ++k) {
                    result(row, col) += (matrix1_(row, 2 * k) + matrix2_(2 * k + 1, col)) *
                                        (matrix1_(row, 2 * k + 1) + matrix2_(2 * k, col));
                }
            }
        }

        return result;
    }

    void Winograd::ComputeAdditionPar(Matrix<double> &result) const {
        std::size_t n = matrix1_.getRows(), m = matrix2_.getCols();

#pragma omp parallel for
        for (std::size_t row = 0; row != n; ++row)
            for (std::size_t col = 0; col != m; ++col)
                result(row, col) += matrix1_(row, n - 1) * matrix2_(n - 1, col);
    }

    void Winograd::ComputeAdditionSeq(Matrix<double> &result) const {
        std::size_t n = matrix1_.getRows(), m = matrix2_.getCols();

        for (std::size_t row = 0; row != n; ++row)
            for (std::size_t col = 0; col != m; ++col)
                result(row, col) += matrix1_(row, m - 1) * matrix2_(n - 1, col);
    }

    bool Winograd::MatrixesIsInValid() const {
        if (matrix1_.getCols() != matrix2_.getRows()) {
            std::cerr << "Invalid matrices size" << std::endl;
            return true;
        }

        if (matrix1_.getRows() == 0 or matrix1_.getCols() == 0 or
            matrix2_.getRows() == 0 or matrix2_.getCols() == 0) {
            std::cerr << "Empty matrices" << std::endl;
            return true;
        }

        return false;
    }
}  // namespace s21