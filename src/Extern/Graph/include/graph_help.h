#ifndef A3_PARALLELS_EXTERN_GRAPH_INCLUDE_GRAPH_HELP_H_
#define A3_PARALLELS_EXTERN_GRAPH_INCLUDE_GRAPH_HELP_H_

#include <cctype>
#include <iostream>
#include <type_traits>
#include <vector>

#include "inf.h"

namespace ng {
    enum class GraphType : int {
        kEmptyGraph,
        kDirectedGraph,
        kUndirectedGraph,
        kMultiGraph
    };

    enum class GraphDebugMode : int {
        kDoesntPrintAdjacencyMatrix,
        kPrintAdjacencyMatrix
    };

    template<typename T>
    struct GraphEdge {
        static_assert(std::is_fundamental<T>::value,
                      "Template parameter T must be fundamental");

        std::size_t from{}, to{};
        T weight{};

        GraphEdge() = default;

        GraphEdge(std::size_t from, std::size_t to, T weight)
                : from(from), to(to), weight(weight) {}

        static GraphEdge UndetectedEdge() {
            return GraphEdge(kInf<std::size_t>, kInf<std::size_t>, kInf<T>);
        }
    };

    template<typename T>
    using edge_vector = std::vector<GraphEdge<T>>;

}  // namespace ng

#endif  // A3_PARALLELS_EXTERN_GRAPH_INCLUDE_GRAPH_HELP_H_
