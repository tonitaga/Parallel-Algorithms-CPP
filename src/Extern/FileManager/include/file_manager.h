#ifndef A3_PARALLELS_EXTERN_GRAPH_INCLUDE_FILE_MANAGER_H_
#define A3_PARALLELS_EXTERN_GRAPH_INCLUDE_FILE_MANAGER_H_

#include <string_view>

#include "graph_help.h"
#include "matrix.h"

namespace ng {
    class FileManager final {
    public:
        template<typename T>
        static Matrix<T> ReadMatrixFromFile(std::string_view path, T);

        template<typename T>
        static void SaveMatrixIntoFile(std::string_view path,
                                       const Matrix<T> &matrix);
    };
}  // namespace ng

#include "file_manager.tpp"

#endif  // A3_PARALLELS_EXTERN_GRAPH_INCLUDE_FILE_MANAGER_H_
