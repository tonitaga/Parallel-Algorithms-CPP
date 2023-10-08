#ifndef A3_PARALLELS_MODEL_MODEL_H_
#define A3_PARALLELS_MODEL_MODEL_H_

#include "graph.h"

#ifdef ANT_COLONY
#include "ant_colony.h"
#endif  // ANT_COLONY

#ifdef GAUSS
#include "gauss.h"
#endif  // GAUSS

#ifdef WINOGRAD
#include "winograd.h"
#endif  // WINOGRAD

#include <chrono>

namespace s21 {
    class Model final {
    public:
        void CreateMatrixAndFillRandomly(std::size_t square, double left,
                                         double right);

#ifdef ANT_COLONY

        AntColonyTimed SolveSalesmansProblemSequence();
        AntColonyTimed SolveSalesmansProblemParallel();

        void LoadGraphFromFile(std::string_view path);
        void ExportMatrixIntoFile(std::string_view path);
        void DebugGraph();
        void setGraphDebugMode(GraphDebugMode mode);

#endif  // ANT_COLONY

#ifdef GAUSS
        GaussTimed SolveSystemOfLinearAlgebraicEquationsSequence();
        GaussTimed SolveSystemOfLinearAlgebraicEquationsParallel();

        void LoadMatrixFromFile(std::string_view path);
        void DebugMatrix();
#endif  // GAUSS

#ifdef WINOGRAD
        WinogradTimed MulMatricesNaive();
        WinogradTimed MulMatricesSimple();
        WinogradTimed MulMatricesUsingThreads(std::size_t threads_count = 2);
        WinogradTimed MullMatricesUsingPipelineParallelism(
            std::size_t threads_count = 2);

        void LoadMatricesFromFile(std::string_view path1, std::string_view path2);
        void DebugMatrices();
#endif  // WINOGRAD
    private:
#ifdef ANT_COLONY
        Graph<double> graph_;
#endif  // ANT_COLONY

#ifdef GAUSS
        Matrix<double> matrix_;
#endif  // GAUSS

#ifdef WINOGRAD
        Winograd winograd;
        Matrix<double> matrix1_, matrix2_;
#endif  // WINOGRAD

        template<typename FunctionCalling>
        double getComputingTime(FunctionCalling calling) {
            using namespace std::chrono;
            auto begin = high_resolution_clock::now();
            calling();
            auto end = high_resolution_clock::now();
            return duration_cast<nanoseconds>(end - begin).count() / 1'000'000.0;
        }
    };
}  // namespace s21

#endif  // A3_PARALLELS_MODEL_MODEL_H_
