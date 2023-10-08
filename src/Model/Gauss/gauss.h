#ifndef A3_PARALLELS_MODEL_GAUSS_GAUSS_H_
#define A3_PARALLELS_MODEL_GAUSS_GAUSS_H_

#include <mutex>

#include "matrix.h"

namespace ng {
    using GaussTimed = std::pair<std::vector<double>, double>;

    class Gauss final {
    public:
        explicit Gauss(const Matrix<double> &m) : matrix_(m) {};

        [[nodiscard]] bool isGoodMatrix() const noexcept {
            return matrix_.getRows() + 1 == matrix_.getCols();
        }

        std::vector<double> SolveSystemOfLinearAlgebraicEquationsSequence();
        std::vector<double> SolveSystemOfLinearAlgebraicEquationsParallel();

    private:
        Matrix<double> matrix_;
        std::mutex mutex_;
    };
}  // namespace ng

#endif  // A3_PARALLELS_MODEL_GAUSS_GAUSS_H_
