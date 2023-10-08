#ifndef A3_PARALLELS_MODEL_ANT_COLONY_SINGLE_THREAD_ANT_COLONY_H_
#define A3_PARALLELS_MODEL_ANT_COLONY_SINGLE_THREAD_ANT_COLONY_H_

#include "ant.h"
#include "graph.h"

namespace s21 {
    using AntColonyTimed = std::pair<AntPath, double>;

    class AntColonyOptimization {
    public:
        explicit AntColonyOptimization(const Graph<double> &graph);
        explicit AntColonyOptimization(Graph<double> &&graph);

        AntPath SolveSalesmanProblemSequence(bool reset = false);
        AntPath SolveSalesmanProblemParallel(bool reset = false);

    private:
        Graph<double> graph_;
        Matrix<double> pheromone_;

        std::vector<Ant> ants_;

    private:
        // Help constants
        const double kQAspect_ = 0.015;
        const double kMinimalPheromone = 0.01;
        const std::size_t kMaxIterationsWithoutImprovement = 75;
        const std::size_t kThreadsStartVertexesCount = 50;

    private:
        // Main constants
        const double kAlpha_ = 1.0;
        const double kBeta_ = 2.0;
        const double kPheromone0_ = 1;
        const double kQ_ = 5.0;
        const double kEvaporation_ = 0.2;

    private:
        void InitializeStartPheromone();

        void CreateAntsSeq();
        void CreateAntsPar();

        void LaunchAntsSeq();
        void LaunchAntsPar();

        bool UpdatePathAndLocalPheromoneSeq(AntPath &path, Matrix<double> &lpu);
        bool UpdatePathAndLocalPheromonePar(AntPath &path, Matrix<double> &lpu);

        void UpdateGlobalPheromone(const Matrix<double> &local_pheromone);
    };
}  // namespace s21

#endif  // A3_PARALLELS_MODEL_ANT_COLONY_SINGLE_THREAD_ANT_COLONY_H_
