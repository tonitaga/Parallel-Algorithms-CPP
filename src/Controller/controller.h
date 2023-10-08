#ifndef A3_PARALLELS_CONTROLLER_CONTROLLER_H_
#define A3_PARALLELS_CONTROLLER_CONTROLLER_H_

#include "model.h"

namespace s21 {
    class Controller final {
    public:
        explicit Controller(Model *model) : model_(model) {};
        Controller(const Controller &) = delete;
        Controller &operator=(const Controller &) = delete;

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
        Model *model_;
    };
}  // namespace s21

#endif  // A3_PARALLELS_CONTROLLER_CONTROLLER_H_
