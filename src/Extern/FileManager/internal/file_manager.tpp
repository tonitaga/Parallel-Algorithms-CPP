#ifndef A3_PARALLELS_EXTERN_GRAPH_INTERNAL_FILE_MANAGER_TPP_
#define A3_PARALLELS_EXTERN_GRAPH_INTERNAL_FILE_MANAGER_TPP_

#include <fstream>
#include <iostream>

#include "file_manager.h"

namespace s21 {
    template<typename T>
    Matrix<T> FileManager::ReadMatrixFromFile(std::string_view path, T) {
        Matrix<T> read_data;
        try {
            std::ifstream file(path.data());

            if (!file.is_open()) {
                std::cerr << "File doesn't exists!" << std::endl;
                return {};
            }

            std::size_t rows, cols;
            file >> rows >> cols;

            Matrix<T> data(rows, cols, T{});
            for (std::size_t row = 0; row != rows; ++row)
                for (std::size_t col = 0; col != cols; ++col) file >> data(row, col);

            read_data = std::move(data);

            file.close();

        } catch (std::exception &e) {
            std::cerr << "Exception caught! Info: " << e.what() << std::endl;
            read_data = Matrix<T>{};
        }

        return read_data;
    }

    template<typename T>
    void FileManager::SaveMatrixIntoFile(std::string_view path,
                                         const Matrix<T> &m) {
        try {
            std::ofstream file(path.data());

            if (!file.is_open()) {
                std::cerr << "File doesn't created!" << std::endl;
                return;
            }

            file << m.getRows() << ' ' << m.getCols() << '\n';
            file << m << std::endl;
            file.close();

        } catch (std::exception &e) {
            std::cerr << "Exception caught! Info: " << e.what() << std::endl;
        }
    }
}  // namespace s21

#endif  // A3_PARALLELS_EXTERN_GRAPH_INTERNAL_FILE_MANAGER_TPP_
