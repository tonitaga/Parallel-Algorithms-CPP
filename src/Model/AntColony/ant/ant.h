#ifndef A3_PARALLELS_MODEL_ANT_COLONY_ANT_ANT_H_
#define A3_PARALLELS_MODEL_ANT_COLONY_ANT_ANT_H_

#include "ant_path.h"
#include "graph.h"

namespace s21 {
    struct Ant final {
        explicit Ant(std::size_t start_vertex = 0)
                : start_location(start_vertex), current_location(start_vertex) {};

        AntPath path;
        std::vector<std::size_t> visited;
        std::size_t start_location = 0;
        std::size_t current_location = 0;
        bool can_continue = true;

        void MakeChoice(const Graph<double> &, const Matrix<double> &, double,
                        double);

        std::vector<std::size_t> getNeighborVertexes(const Graph<double> &);

        [[nodiscard]] std::vector<double> getChoosingProbability(
                const Graph<double> &, const Matrix<double> &,
                const std::vector<std::size_t> &, double, double) const;

        void CalculateNextVertex(const Graph<double> &, const std::vector<double> &,
                                 const std::vector<std::size_t> &);

        static double GetRandomChoice();
    };
}  // namespace s21

#endif  // A3_PARALLELS_MODEL_ANT_COLONY_ANT_ANT_H_
