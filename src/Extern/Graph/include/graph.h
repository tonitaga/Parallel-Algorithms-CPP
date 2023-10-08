#ifndef A3_PARALLELS_EXTERN_GRAPH_INCLUDE_GRAPH_H_
#define A3_PARALLELS_EXTERN_GRAPH_INCLUDE_GRAPH_H_

#include <string_view>

#include "file_manager.h"

namespace ng {
    template<typename T>
    class Graph final {
        static_assert(std::is_integral<T>::value or std::is_floating_point<T>::value,
                      "Template parameter T must be integral or floating point");

    public:
        using size_type = std::size_t;
        using value_type = T;
        using const_reference = const T &;
        using edge_type = GraphEdge<T>;

    public:
        Graph() noexcept = default;

        explicit Graph(const Matrix<value_type> &adjacency_matrix);
        explicit Graph(std::string_view file_path);

        void LoadGraphFromFile(std::basic_string_view<char> file_path);

        [[nodiscard]] bool isEmpty() const noexcept;

        [[nodiscard]] size_type getVertexesCount() const noexcept;
        [[nodiscard]] size_type getEdgesCount() const noexcept;
        [[nodiscard]] GraphType getGraphType() const noexcept;
        [[nodiscard]] GraphDebugMode getDebugMode() const noexcept;
        value_type getGraphWeight() const noexcept;
        edge_vector<value_type> getEdges() const noexcept;
        Matrix<value_type> getAdjacencyMatrix() const noexcept;
        static std::string getStringFromGraphType(GraphType type);

        const_reference operator()(size_type from, size_type to) const;

        void setDebugMode(GraphDebugMode debug_mode);

    private:
        Matrix<value_type> adjacency_matrix_;
        edge_vector<value_type> edges_;
        value_type default_value_{};
        value_type weight_{};
        GraphType graph_type_ = GraphType::kEmptyGraph;
        GraphDebugMode graph_debug_mode_ =
                GraphDebugMode::kDoesntPrintAdjacencyMatrix;

    private:
        void CountEdgesAndGraphType();
    };

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Graph<T> &graph);
}  // namespace ng

#include "graph.tpp"

#endif  // A3_PARALLELS_EXTERN_GRAPH_INCLUDE_GRAPH_H_
