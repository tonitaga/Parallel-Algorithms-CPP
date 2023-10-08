#include "model.h"

namespace ng {
    void Model::CreateMatrixAndFillRandomly(std::size_t square, double left,
                                            double right) {
#ifdef ANT_COLONY
        Matrix<double> matrix =
                Matrix<double>::RandomAdjacencyMatrix(square, left, right);
        auto debug_mode = graph_.getDebugMode();
        graph_ = Graph<double>(matrix);
        graph_.setDebugMode(debug_mode);
#endif  // ANT_COLONY
#ifdef GAUSS
        Matrix<double> m(square, square + 1, 0.0);
        m.FillRandomly(left, right);
        matrix_ = std::move(m);
#endif  // GAUSS
#ifdef WINOGRAD
        Matrix<double> m1(square, 0.0), m2(square, 0.0);
        m1.FillRandomly(left, right), m2.FillRandomly(left, right);
        matrix1_ = std::move(m1), matrix2_ = std::move(m2);
#endif  // WINOGRAD
    }

#ifdef ANT_COLONY

    AntColonyTimed Model::SolveSalesmansProblemParallel() {
        AntColonyOptimization ant_colony(graph_);
        AntColonyTimed answer;
        answer.second = getComputingTime(
                [&]() { answer.first = ant_colony.SolveSalesmanProblemParallel(); });
        return answer;
    }

    AntColonyTimed Model::SolveSalesmansProblemSequence() {
        AntColonyOptimization ant_colony(graph_);
        AntColonyTimed answer;
        answer.second = getComputingTime(
                [&]() { answer.first = ant_colony.SolveSalesmanProblemSequence(); });
        return answer;
    }

    void Model::LoadGraphFromFile(std::string_view path) {
        graph_.LoadGraphFromFile(path);
    }

    void Model::ExportMatrixIntoFile(std::string_view path) {
        FileManager::SaveMatrixIntoFile(path, graph_.getAdjacencyMatrix());
    }

    void Model::DebugGraph() { std::cout << graph_ << std::endl; }

    void Model::setGraphDebugMode(GraphDebugMode mode) {
        graph_.setDebugMode(mode);
    }

#endif  // ANT_COLONY

#ifdef GAUSS
    GaussTimed Model::SolveSystemOfLinearAlgebraicEquationsSequence() {
      Gauss gauss(matrix_);
      GaussTimed answer;
      answer.second = getComputingTime([&]() {
        answer.first = gauss.SolveSystemOfLinearAlgebraicEquationsSequence();
      });
      return answer;
    }

    GaussTimed Model::SolveSystemOfLinearAlgebraicEquationsParallel() {
      Gauss gauss(matrix_);
      GaussTimed answer;
      answer.second = getComputingTime([&]() {
        answer.first = gauss.SolveSystemOfLinearAlgebraicEquationsParallel();
      });
      return answer;
    }

    void Model::LoadMatrixFromFile(std::string_view path) {
      matrix_ = FileManager::ReadMatrixFromFile(path, 0.0);
    }

    void Model::DebugMatrix() { std::cout << matrix_ << std::endl; }
#endif  // GAUSS

#ifdef WINOGRAD
    WinogradTimed Model::MulMatricesNaive() {
      winograd.setMatrices(matrix1_, matrix2_);
      WinogradTimed answer;
      answer.second =
          getComputingTime([&]() { answer.first = winograd.MultiplyNaive(); });
      return answer;
    }

    WinogradTimed Model::MulMatricesSimple() {
      winograd.setMatrices(matrix1_, matrix2_);
      WinogradTimed answer;
      answer.second =
          getComputingTime([&]() { answer.first = winograd.MultiplySimple(); });
      return answer;
    }

    WinogradTimed Model::MulMatricesUsingThreads(std::size_t threads_count) {
      winograd.setMatrices(matrix1_, matrix2_);
      WinogradTimed answer;
      answer.second = getComputingTime(
          [&]() { answer.first = winograd.MultiplyUsingThreads(threads_count); });
      return answer;
    }

    WinogradTimed Model::MullMatricesUsingPipelineParallelism(
        std::size_t threads_count) {
      winograd.setMatrices(matrix1_, matrix2_);
      WinogradTimed answer;
      answer.second = getComputingTime([&]() {
        answer.first = winograd.MultiplyUsingPipelineParallelism(threads_count);
      });
      return answer;
    }

    void Model::LoadMatricesFromFile(std::string_view path1,
                                     std::string_view path2) {
      matrix1_ = FileManager::ReadMatrixFromFile(path1, 0.0);
      matrix2_ = FileManager::ReadMatrixFromFile(path2, 0.0);
    }

    void Model::DebugMatrices() {
      std::cout << "Matrix #1" << std::endl;
      std::cout << matrix1_ << std::endl;
      std::cout << std::endl;
      std::cout << "Matrix #2" << std::endl;
      std::cout << matrix2_ << std::endl;
    }

#endif  // WINOGRAD
}  // namespace ng
