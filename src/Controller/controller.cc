#include "controller.h"

namespace s21 {
    void Controller::CreateMatrixAndFillRandomly(std::size_t square, double left,
                                                 double right) {
        model_->CreateMatrixAndFillRandomly(square, left, right);
    }

#ifdef ANT_COLONY

    AntColonyTimed Controller::SolveSalesmansProblemSequence() {
        return model_->SolveSalesmansProblemSequence();
    }

    AntColonyTimed Controller::SolveSalesmansProblemParallel() {
        return model_->SolveSalesmansProblemParallel();
    }

    void Controller::LoadGraphFromFile(std::string_view path) {
        model_->LoadGraphFromFile(path);
    }

    void Controller::ExportMatrixIntoFile(std::string_view path) {
        model_->ExportMatrixIntoFile(path);
    }

    void Controller::DebugGraph() { model_->DebugGraph(); }

    void Controller::setGraphDebugMode(GraphDebugMode mode) {
        model_->setGraphDebugMode(mode);
    }

#endif  // ANT_COLONY

#ifdef GAUSS
    GaussTimed Controller::SolveSystemOfLinearAlgebraicEquationsSequence() {
      return model_->SolveSystemOfLinearAlgebraicEquationsSequence();
    }

    GaussTimed Controller::SolveSystemOfLinearAlgebraicEquationsParallel() {
      return model_->SolveSystemOfLinearAlgebraicEquationsParallel();
    }

    void Controller::LoadMatrixFromFile(std::string_view path) {
      model_->LoadMatrixFromFile(path);
    }

    void Controller::DebugMatrix() { model_->DebugMatrix(); }
#endif  // GAUSS

#ifdef WINOGRAD
    WinogradTimed Controller::MulMatricesNaive() {
      return model_->MulMatricesNaive();
    }

    WinogradTimed Controller::MulMatricesSimple() {
      return model_->MulMatricesSimple();
    }

    WinogradTimed Controller::MulMatricesUsingThreads(std::size_t threads_count) {
      return model_->MulMatricesUsingThreads(threads_count);
    }

    WinogradTimed Controller::MullMatricesUsingPipelineParallelism(
        std::size_t threads_count) {
      return model_->MullMatricesUsingPipelineParallelism(threads_count);
    }

    void Controller::LoadMatricesFromFile(std::string_view path1,
                                          std::string_view path2) {
      model_->LoadMatricesFromFile(path1, path2);
    }

    void Controller::DebugMatrices() { model_->DebugMatrices(); }

#endif  // WINOGRAD
}  // namespace s21
