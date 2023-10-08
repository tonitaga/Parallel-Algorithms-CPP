#include "ant_colony.h"

#include <algorithm>
#include <execution>

namespace s21 {
    AntColonyOptimization::AntColonyOptimization(const Graph<double> &graph)
            : graph_(graph), kQ_(kQAspect_ * graph.getGraphWeight()) {
        InitializeStartPheromone();
    }

    AntColonyOptimization::AntColonyOptimization(Graph<double> &&graph)
            : graph_(std::move(graph)), kQ_(kQAspect_ * graph_.getGraphWeight()) {
        InitializeStartPheromone();
    }

    void AntColonyOptimization::InitializeStartPheromone() {
        const std::size_t kVertexesCount = graph_.getVertexesCount();
        Matrix<double> matrix(kVertexesCount);
        for (std::size_t row = 0; row != kVertexesCount; ++row)
            for (std::size_t col = 0; col != kVertexesCount; ++col)
                if (row != col) matrix(row, col) = kPheromone0_;
        pheromone_ = std::move(matrix);
    }

    AntPath AntColonyOptimization::SolveSalesmanProblemSequence(bool reset) {
        if (graph_.isEmpty()) return {};

        const std::size_t kVertexesCount = graph_.getVertexesCount();
        std::size_t counter = 0;

        AntPath path;
        path.distance = kInf<double>;

        while (counter++ != kMaxIterationsWithoutImprovement) {
            Matrix<double> local_pheromone(kVertexesCount, 0.0);

            CreateAntsSeq();
            LaunchAntsSeq();
            if (UpdatePathAndLocalPheromoneSeq(path, local_pheromone))
                if (reset) counter = 0;

            UpdateGlobalPheromone(local_pheromone);
        }

        return path;
    }

    AntPath AntColonyOptimization::SolveSalesmanProblemParallel(bool reset) {
        if (graph_.isEmpty()) return {};

        const std::size_t kVertexesCount = graph_.getVertexesCount();
        std::size_t counter = 0;

        AntPath path;
        path.distance = kInf<double>;

        while (counter++ != kMaxIterationsWithoutImprovement) {
            Matrix<double> local_pheromone(kVertexesCount, 0.0);

            CreateAntsPar();
            LaunchAntsPar();
            if (UpdatePathAndLocalPheromonePar(path, local_pheromone))
                if (reset) counter = 0;

            UpdateGlobalPheromone(local_pheromone);
        }

        return path;
    }

    void AntColonyOptimization::UpdateGlobalPheromone(const Matrix<double> &lpu) {
        // lpu - local pheromone update
        for (std::size_t from = 0, size = lpu.getRows(); from != size; ++from) {
            for (std::size_t to = 0; to != size; ++to) {
                pheromone_(from, to) =
                        (1 - kEvaporation_) * pheromone_(from, to) + lpu(from, to);
                if (pheromone_(from, to) < kMinimalPheromone and from != to)
                    pheromone_(from, to) = kMinimalPheromone;
            }
        }
    }

    void AntColonyOptimization::CreateAntsSeq() {
        const auto kAntsCount = graph_.getVertexesCount();
        ants_.resize(kAntsCount);

        for (std::size_t i = 0; i != kAntsCount; ++i) ants_[i] = Ant(i);
    }

    void AntColonyOptimization::CreateAntsPar() {
        const auto kAntsCount = graph_.getVertexesCount();
        ants_.resize(kAntsCount);

        int start_vertex = 0;
        std::for_each(std::execution::par, ants_.begin(), ants_.end(),
                      [&](Ant &ant) { ant = Ant(start_vertex++); });
    }

    void AntColonyOptimization::LaunchAntsSeq() {
        for (auto &ant: ants_) {
            while (ant.can_continue)
                ant.MakeChoice(graph_, pheromone_, kAlpha_, kBeta_);
        }
    }

    void AntColonyOptimization::LaunchAntsPar() {
        if (graph_.getVertexesCount() >= kThreadsStartVertexesCount) {
            std::vector<std::thread> threads;
            for (auto &ant: ants_) {
                threads.emplace_back([&]() {
                    while (ant.can_continue)
                        ant.MakeChoice(graph_, pheromone_, kAlpha_, kBeta_);
                });
            }

            for (auto &thread: threads)
                if (thread.joinable()) thread.join();
        } else {
            std::for_each(std::execution::par, ants_.begin(), ants_.end(),
                          [&](Ant &ant) {
                              while (ant.can_continue)
                                  ant.MakeChoice(graph_, pheromone_, kAlpha_, kBeta_);
                          });
        }
    }

    bool AntColonyOptimization::UpdatePathAndLocalPheromoneSeq(
            AntPath &path, Matrix<double> &lpu) {
        bool shorter_path_is_find = false;
        for (const auto &ant: ants_) {
            auto ant_path = ant.path;
            if (ant_path.vertices.size() == graph_.getVertexesCount() + 1) {
                if (path.distance > ant.path.distance) {
                    path = ant.path;
                    shorter_path_is_find = true;
                }

                for (std::size_t v = 0; v != ant_path.vertices.size() - 1; ++v)
                    lpu(ant_path.vertices[v], ant_path.vertices[v + 1]) +=
                            kQ_ / ant_path.distance;
            }
        }
        return shorter_path_is_find;
    }

    bool AntColonyOptimization::UpdatePathAndLocalPheromonePar(
            AntPath &path, Matrix<double> &lpu) {
        bool shorter_path_is_find = false;

        std::for_each(
                std::execution::seq, ants_.begin(), ants_.end(), [&](const Ant &ant) {
                    auto ant_path = ant.path;
                    if (ant_path.vertices.size() == graph_.getVertexesCount() + 1) {
                        if (path.distance > ant.path.distance) {
                            path = ant.path;
                            shorter_path_is_find = true;
                        }

                        for (std::size_t v = 0; v != ant_path.vertices.size() - 1; ++v)
                            lpu(ant_path.vertices[v], ant_path.vertices[v + 1]) +=
                                    kQ_ / ant_path.distance;
                    }
                });

        return shorter_path_is_find;
    }
}  // namespace s21