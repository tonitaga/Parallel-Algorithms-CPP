#ifndef A3_PARALLELS_EXTERN_GRAPH_INTERNAL_GRAPH_TPP_
#define A3_PARALLELS_EXTERN_GRAPH_INTERNAL_GRAPH_TPP_

#include "graph.h"

namespace s21 {
    template<typename T>
    Graph<T>::Graph(const Matrix<value_type> &adjacency_matrix)
            : adjacency_matrix_(adjacency_matrix) {
        CountEdgesAndGraphType();
    }

    template<typename T>
    Graph<T>::Graph(std::string_view file_path)
            : adjacency_matrix_(FileManager::ReadMatrixFromFile(file_path, T{})) {
        CountEdgesAndGraphType();
    }

    template<typename T>
    void Graph<T>::LoadGraphFromFile(std::basic_string_view<char> file_path) {
        adjacency_matrix_ = FileManager::ReadMatrixFromFile(file_path, T{});
        CountEdgesAndGraphType();
    }

    template<typename T>
    bool Graph<T>::isEmpty() const noexcept {
        return adjacency_matrix_.getRows() == 0;
    }

    template<typename T>
    T Graph<T>::getGraphWeight() const noexcept {
        return weight_;
    }

    template<typename T>
    typename Graph<T>::size_type Graph<T>::getVertexesCount() const noexcept {
        return adjacency_matrix_.getRows();
    }

    template<typename T>
    typename Graph<T>::size_type Graph<T>::getEdgesCount() const noexcept {
        return edges_.size();
    }

    template<typename T>
    GraphType Graph<T>::getGraphType() const noexcept {
        return graph_type_;
    }

    template<typename T>
    edge_vector<T> Graph<T>::getEdges() const noexcept {
        return edges_;
    }

    template<typename T>
    Matrix<T> Graph<T>::getAdjacencyMatrix() const noexcept {
        return adjacency_matrix_;
    }

    template<typename T>
    GraphDebugMode Graph<T>::getDebugMode() const noexcept {
        return graph_debug_mode_;
    }

    template<typename T>
    void Graph<T>::setDebugMode(GraphDebugMode debug_mode) {
        graph_debug_mode_ = debug_mode;
    }

    template<typename T>
    typename Graph<T>::const_reference Graph<T>::operator()(size_type from,
                                                            size_type to) const {
        return adjacency_matrix_(from, to);
    }

    template<typename T>
    void Graph<T>::CountEdgesAndGraphType() {
        edges_.clear();
        weight_ = value_type{};
        graph_type_ = GraphType::kEmptyGraph;

        bool is_directed = true, is_undirected = true;
        for (size_type from = 0, size = getVertexesCount(); from != size; ++from) {
            for (size_type to = from; to != size; ++to) {
                if (from == to and adjacency_matrix_(from, to) != default_value_) {
                    edges_.emplace_back(from, to, adjacency_matrix_(from, to));
                    weight_ += adjacency_matrix_(from, to);

                } else if (adjacency_matrix_(from, to) != default_value_ and
                           adjacency_matrix_(to, from) != default_value_ and
                           adjacency_matrix_(from, to) != adjacency_matrix_(to, from)) {
                    edges_.emplace_back(from, to, adjacency_matrix_(from, to));
                    weight_ += adjacency_matrix_(from, to);
                    edges_.emplace_back(to, from, adjacency_matrix_(to, from));
                    weight_ += adjacency_matrix_(to, from);

                } else if (adjacency_matrix_(from, to) != default_value_ and
                           adjacency_matrix_(to, from) != default_value_) {
                    edges_.emplace_back(from, to, adjacency_matrix_(from, to));
                    weight_ += adjacency_matrix_(from, to);
                    is_directed = false;

                } else if (adjacency_matrix_(from, to) != default_value_ or
                           adjacency_matrix_(to, from) != default_value_) {
                    if (adjacency_matrix_(from, to) != default_value_)
                        edges_.emplace_back(from, to, adjacency_matrix_(from, to));
                    else
                        edges_.emplace_back(to, from, adjacency_matrix_(from, to));
                    weight_ += adjacency_matrix_(from, to);
                    is_undirected = false;
                }
            }
        }

        if (edges_.empty()) return;

        if (is_directed)
            graph_type_ = GraphType::kDirectedGraph;
        else if (is_undirected)
            graph_type_ = GraphType::kUndirectedGraph;
        else
            graph_type_ = GraphType::kMultiGraph;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Graph<T> &graph) {
        out << "Graph information:\n\t";
        out << "Vertexes count: " << graph.getVertexesCount() << "\n\t";
        out << "Edges count:    " << graph.getEdgesCount() << "\n\t";
        out << "Graph type:     "
            << graph.getStringFromGraphType(graph.getGraphType()) << "\n\t";
        out << "Graph weight:   " << graph.getGraphWeight() << "\n\t";

        if (graph.getDebugMode() == GraphDebugMode::kPrintAdjacencyMatrix) {
            out << "Adjacency Matrix:\n";
            out << graph.getAdjacencyMatrix();
        }

        return out;
    }

    template<typename T>
    std::string Graph<T>::getStringFromGraphType(GraphType type) {
        std::string str = "kEmptyGraph";

        if (type == GraphType::kDirectedGraph)
            str = "kDirectedGraph";
        else if (type == GraphType::kUndirectedGraph)
            str = "kUndirectedGraph";
        else if (type == GraphType::kMultiGraph)
            str = "kMultiGraph";

        return str;
    }
}  // namespace s21

#endif  // A3_PARALLELS_EXTERN_GRAPH_INTERNAL_GRAPH_TPP_
