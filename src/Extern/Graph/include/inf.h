#ifndef A3_PARALLELS_EXTERN_GRAPH_INCLUDE_INF_H_
#define A3_PARALLELS_EXTERN_GRAPH_INCLUDE_INF_H_

#include <limits>

namespace ng {
    template<typename T>
    constexpr T kInf = std::numeric_limits<T>::max();
}

#endif  // A3_PARALLELS_EXTERN_GRAPH_INCLUDE_INF_H_
