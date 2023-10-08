#include "ant.h"

#include <chrono>
#include <random>

namespace s21 {
    void Ant::MakeChoice(const Graph<double> &graph,
                         const Matrix<double> &pheromone, double alpha,
                         double beta) {
        if (path.vertices.empty()) {
            path.vertices.push_back(current_location);
            visited.push_back(current_location);
        }

        std::vector<std::size_t> neighbor_vertexes = getNeighborVertexes(graph);

        if (neighbor_vertexes.empty()) {
            can_continue = false;
            if (graph(current_location, start_location) != 0) {
                path.vertices.push_back(start_location);
                path.distance += graph(current_location, start_location);
            }
            return;
        }

        std::vector<double> choosing_probability =
                getChoosingProbability(graph, pheromone, neighbor_vertexes, alpha, beta);

        CalculateNextVertex(graph, choosing_probability, neighbor_vertexes);
    }

    double Ant::GetRandomChoice() {
        std::uniform_real_distribution<> dist(0.0, 1.0);
        std::default_random_engine re(
                std::chrono::system_clock::now().time_since_epoch().count());
        return dist(re);
    }

    std::vector<std::size_t> Ant::getNeighborVertexes(const Graph<double> &graph) {
        std::vector<std::size_t> neighbor_vertexes;
        for (std::size_t to = 0; to != graph.getVertexesCount(); ++to)
            if (graph(current_location, to) != 0 and
                std::find(visited.begin(), visited.end(), to) == visited.end())
                neighbor_vertexes.push_back(to);
        return neighbor_vertexes;
    }

    std::vector<double> Ant::getChoosingProbability(
            const Graph<double> &g, const Matrix<double> &p,
            const std::vector<std::size_t> &nv, double alpha, double beta) const {
        // nv - neighbor vertexes; g - graph, p - pheromone
        std::vector<double> choosing_probability(nv.size());

        {
            std::vector<double> wish;
            std::vector<double> probability;
            double summary_wish = 0.0f;
            for (auto v: nv) {
                double t = p(current_location, v);
                double w = g(current_location, v);
                double n = 1 / w;
                wish.push_back(std::pow(t, alpha) * std::pow(n, beta));
                summary_wish += wish.back();
            }

            for (std::size_t neighbor = 0; neighbor != nv.size(); ++neighbor) {
                probability.push_back(wish[neighbor] / summary_wish);
                if (neighbor == 0)
                    choosing_probability[neighbor] = probability.back();
                else
                    choosing_probability[neighbor] =
                            choosing_probability[neighbor - 1] + probability.back();
            }
        }

        return choosing_probability;
    }

    void Ant::CalculateNextVertex(
            const Graph<double> &graph, const std::vector<double> &choosing_probability,
            const std::vector<std::size_t> &neighbor_vertexes) {
        std::size_t next_vertex = 0;
        double choose = GetRandomChoice();

        for (std::size_t neighbor = 0; neighbor != neighbor_vertexes.size();
             ++neighbor) {
            if (choose <= choosing_probability[neighbor]) {
                next_vertex = neighbor_vertexes[neighbor];
                break;
            }
        }

        path.vertices.push_back(next_vertex);
        visited.push_back(next_vertex);
        path.distance += graph(current_location, next_vertex);
        current_location = next_vertex;
    }
}  // namespace s21