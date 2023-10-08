#ifndef A3_PARALLELS_MODEL_WINOGRAD_WINOGRAD_H_
#define A3_PARALLELS_MODEL_WINOGRAD_WINOGRAD_H_

#include <execution>

#include "matrix.h"

namespace s21 {
    using WinogradTimed = std::pair<Matrix<double>, double>;

    class Winograd final {
    public:
        Winograd() noexcept = default;
        Winograd(const Matrix<double> &m1, const Matrix<double> &m2);
        Winograd(Matrix<double> &&m1, Matrix<double> &&m2) noexcept;
        Winograd(std::size_t rows1, std::size_t cols1, std::size_t rows2,
                 std::size_t cols2);

        void setMatrices(const Matrix<double> &m1, const Matrix<double> &m2);
        void setMatrices(Matrix<double> &&m1, Matrix<double> &&m2) noexcept;
        void setMatrices(std::size_t rows1, std::size_t cols1, std::size_t rows2,
                         std::size_t cols2);

        Matrix<double> MultiplyNaive() const;
        Matrix<double> MultiplySimple() const;
        Matrix<double> MultiplyUsingThreads(std::size_t threads_count) const;
        Matrix<double> MultiplyUsingPipelineParallelism(
                std::size_t threads_count) const;

    private:
        Matrix<double> matrix1_, matrix2_;

        void FillMatricesRandomly();

        std::vector<double> ComputeRowFactorPar() const;
        std::vector<double> ComputeColFactorPar() const;

        Matrix<double> ComputeMultiplicationMainSeq(
                const std::vector<double> &row_factor,
                const std::vector<double> &col_factor) const;

        Matrix<double> ComputeMultiplicationMainPar(
                const std::vector<double> &row_factor,
                const std::vector<double> &col_factor) const;

        void ComputeAdditionPar(Matrix<double> &result) const;
        void ComputeAdditionSeq(Matrix<double> &result) const;

        std::vector<double> ComputeRowFactorSeq() const;
        std::vector<double> ComputeColFactorSeq() const;

        bool MatrixesIsInValid() const;
    };
}  // namespace s21

#endif  // A3_PARALLELS_MODEL_WINOGRAD_WINOGRAD_H_
