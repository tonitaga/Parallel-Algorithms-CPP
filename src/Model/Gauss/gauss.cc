#include "gauss.h"

#include <execution>

namespace ng {
    std::vector<double> Gauss::SolveSystemOfLinearAlgebraicEquationsSequence() {
        if (!isGoodMatrix()) {
            std::cerr << "Matrix is invalid: rows must be equal to cols - 1"
                      << std::endl;
            return {};
        }

        if (matrix_.getRows() < 2) {
            std::cerr << "This is not a system of linear algebraic equation,"
                         "rows count must be at least two!"
                      << std::endl;
            return {};
        }

        std::vector<double> correct_answer;

        try {
            const std::size_t rows = matrix_.getRows();
            const std::size_t cols = matrix_.getCols();

            std::vector<double> answers(matrix_.getRows());

            for (std::size_t k = 1; k != rows; ++k) {
                for (std::size_t j = k; j != rows; ++j) {
                    double m = matrix_(j, k - 1) / matrix_(k - 1, k - 1);
                    for (std::size_t i = 0; i != cols; ++i) {
                        matrix_(j, i) = matrix_(j, i) - m * matrix_(k - 1, i);
                    }
                }
            }

            for (int i = static_cast<int>(rows - 1); i >= 0; --i) {
                answers[i] = matrix_(i, rows) / matrix_(i, i);
                for (int c = static_cast<int>(rows - 1); c != i; --c) {
                    answers[i] -= matrix_(i, c) * answers[c] / matrix_(i, i);
                }
            }

            correct_answer = std::move(answers);

        } catch (std::exception &e) {
            std::cerr << "Caught exception. Info: " << e.what() << std::endl;
            correct_answer = {};
        }

        return correct_answer;
    }

    std::vector<double> Gauss::SolveSystemOfLinearAlgebraicEquationsParallel() {
        if (!isGoodMatrix()) {
            std::cerr << "Matrix is invalid: rows must be equal to cols - 1"
                      << std::endl;
            return {};
        }

        if (matrix_.getRows() < 2) {
            std::cerr << "This is not a system of linear algebraic equation,"
                         "rows count must be at least two!"
                      << std::endl;
            return {};
        }

        std::vector<double> correct_answer;

        try {
            const std::size_t rows = matrix_.getRows();
            const std::size_t cols = matrix_.getCols();

            std::vector<double> answers(matrix_.getRows());

            for (std::size_t k = 1; k != rows; ++k) {
#pragma omp parallel for
                for (std::size_t j = k; j != rows; ++j) {
                    double m = matrix_(j, k - 1) / matrix_(k - 1, k - 1);
                    for (std::size_t i = 0; i != cols; ++i) {
                        matrix_(j, i) -= m * matrix_(k - 1, i);
                    }
                }
            }

            for (int i = static_cast<int>(rows - 1); i >= 0; --i) {
                answers[i] = matrix_(i, rows) / matrix_(i, i);
                for (int c = static_cast<int>(rows - 1); c != i; --c) {
                    answers[i] -= matrix_(i, c) * answers[c] / matrix_(i, i);
                }
            }

            correct_answer = std::move(answers);

        } catch (std::exception &e) {
            std::cerr << "Caught exception. Info: " << e.what() << std::endl;
            correct_answer = {};
        }

        return correct_answer;
    }
}  // namespace ng

/*
     x991 = 2.005677     x992 = 0.554701    x993 = -6.164113    x994 = -9.513835
   x995 = 3.775937 x996 = 4.280491     x997 = 1.677962    x998 = -3.935551 x999
   = -5.828308    x1000 = 5.999081
 */

/*
     x991 = 2.005677     x992 = 0.554701    x993 = -6.164113    x994 = -9.513835
   x995 = 3.775937 x996 = 4.280491     x997 = 1.677962    x998 = -3.935551 x999
   = -5.828308    x1000 = 5.999081
 */
