#ifndef A3_PARALLELS_EXTERN_GRAPH_INCLUDE_MATRIX_H_
#define A3_PARALLELS_EXTERN_GRAPH_INCLUDE_MATRIX_H_

#include <cctype>
#include <ostream>
#include <type_traits>
#include <vector>

namespace s21 {
    template<typename T>
    class Matrix final {
        static_assert(std::is_integral<T>::value or std::is_floating_point<T>::value,
                      "Template parameter T must be integral or floating point");

    public:
        using size_type = std::size_t;
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;

    public:
        Matrix() noexcept = default;
        Matrix(size_type rows, size_type cols, value_type fill);
        explicit Matrix(size_type square, value_type fill = value_type{});
        explicit Matrix(const std::vector<std::vector<value_type>> &vector_matrix);
        Matrix(const Matrix &other);
        Matrix(Matrix &&other) noexcept = default;

        Matrix &operator=(const Matrix &other);
        Matrix &operator=(Matrix &&other) noexcept = default;
        Matrix &operator=(const std::vector<std::vector<value_type>> &vector_matrix);

        [[nodiscard]] size_type getRows() const noexcept;
        [[nodiscard]] size_type getCols() const noexcept;
        [[nodiscard]] size_type getElementCount() const noexcept;
        const_reference getElement(size_type row, size_type col) const;

        [[nodiscard]] bool isSquare() const noexcept;

        void setRows(size_type rows);
        void setCols(size_type cols);

        void Fill(value_type fill = value_type{});
        void FillRandomly(value_type left_border, value_type right_border);

        reference operator()(size_type row, size_type col);
        const_reference operator()(size_type row, size_type col) const;

        bool operator==(const Matrix &other) const;

        std::vector<std::vector<value_type>> toVectorMatrix() const;

        static Matrix<T> RandomAdjacencyMatrix(std::size_t square, T left_border,
                                               T right_border);

    private:
        size_type rows_{}, cols_{};
        std::vector<value_type> data_;
    };

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &rhs);
}  // namespace s21

#include "matrix.tpp"

#endif  // A3_PARALLELS_EXTERN_GRAPH_INCLUDE_MATRIX_H_
