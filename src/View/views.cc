#include "views.h"

#ifdef ANT_COLONY
namespace ng {
    enum class AntChoice : int {
        kExitProgram,
        kCreateAdjacencyMatrixRandomly,
        kReadGraphFromFile,
        kSolveSalesmansProblemInSequence,
        kSolveSalesmansProblemInParallel,
        kSolveSalesmansProblemCompare,
        kExportGraphMatrixIntoFile,
        kShowGraph,
        kChangeSettings
    };

    void AntView::Start() {
        DisplayDescription();
        ConfirmProgramState();
        bool stop = false;

        while (!stop) {
            DisplayMenuHead();
            DisplayMenuItems();

            auto choice = static_cast<AntChoice>(PerformChoice());

            switch (choice) {
                case AntChoice::kExitProgram:
                    stop = true;
                    break;
                case AntChoice::kShowGraph:
                    controller_->DebugGraph();
                    break;
                case AntChoice::kExportGraphMatrixIntoFile:
                    controller_->ExportMatrixIntoFile(
                            PerformStringInput("Enter graph save file path: "));
                    break;
                case AntChoice::kReadGraphFromFile:
                    controller_->LoadGraphFromFile(
                            PerformStringInput("Enter graph read file path: "));
                    break;
                case AntChoice::kCreateAdjacencyMatrixRandomly: {
                    InputUserMatrixCreateData(controller_);
                    break;
                }
                case AntChoice::kSolveSalesmansProblemInSequence:
                    DisplayAntColonySolve(controller_->SolveSalesmansProblemSequence(),
                                          "Salesmans problem solved in sequence");
                    break;
                case AntChoice::kSolveSalesmansProblemInParallel:
                    DisplayAntColonySolve(controller_->SolveSalesmansProblemParallel(),
                                          "Salesmans problem solved in parallel");
                    break;
                case AntChoice::kSolveSalesmansProblemCompare: {
                    LaunchCompareThenDisplay();
                    break;
                }
                case AntChoice::kChangeSettings:
                    ConfirmProgramState();
                    break;
                default:
                    std::cout << red << "Error key code!" << reset << std::endl;
                    break;
            }
        }
    }

    void AntView::DisplayMenuItems() {
        std::cout << red << "1)" << reset << " Create matrix and fill randomly"
                  << std::endl;
        std::cout << red << "2)" << reset << " Load graph from file" << std::endl;
        std::cout << red << "3)" << reset
                  << " Solve traveling salesman problem in sequence" << std::endl;
        std::cout << red << "4)" << reset
                  << " Solve traveling salesman problem in parallel" << std::endl;
        std::cout << red << "5)" << reset
                  << " Compare parallel and sequence realizations" << std::endl;
        std::cout << red << "6)" << reset << " Export graph matrix into file"
                  << std::endl;
        std::cout << red << "7)" << reset << " Show current graph" << std::endl;
        std::cout << red << "8)" << reset << " Change settings" << std::endl;
        DisplayMenuExit();
    }

    void AntView::DisplayAntColonySolve(const AntColonyTimed &ant_timed,
                                        std::string_view message) {
        auto [ant_path, time_ms] = ant_timed;
        std::cout << blue << message << reset << std::endl;
        std::cout << "Distance: " << blue << ant_path.distance << reset << std::endl;

        if (need_print_matrix_) {
            std::cout << "Vertices enter order: " << std::endl;
            for (std::size_t i = 0; i != ant_path.vertices.size(); ++i) {
                if (i != 0 and i % 20 == 0) std::cout << '\n';
                std::cout << blue << ant_path.vertices[i] << ' ';
            }
            std::cout << reset << std::endl;
        }
        std::cout << "Solving time is (ms): " << blue << time_ms << reset
                  << std::endl;
    }

    void AntView::LaunchCompareThenDisplay() {
        int launches_count = PerformIntInput("Enter launches count: ");

        if (launches_count <= 0) {
            std::cout << red << "Launches count mush be at least one!" << reset
                      << std::endl;
            return;
        }

        double sequence_time_ms = 0, parallel_time_ms = 0;

        for (int i = 0; i != launches_count; ++i) {
            sequence_time_ms += controller_->SolveSalesmansProblemSequence().second;
            parallel_time_ms += controller_->SolveSalesmansProblemParallel().second;
        }

        DisplayCompare(sequence_time_ms, parallel_time_ms, launches_count);
    }

    void AntView::DisplayDescription() {
        std::cout << red << "Copyright School21 Students: Tonitaga | Manhunte"
                  << reset << std::endl;
        std::cout << std::endl;
        std::cout << green << "Description:" << reset << std::endl;
        std::cout
                << "\tThe Ant Colony Optimization algorithm is a algorithm\n"
                   "\tinspired by the foraging behavior of ants.\n"
                   "\tIt uses a probabilistic approach to find optimal solutions\n"
                   "\tby simulating the pheromone trail communication and collective "
                   "decision-making of ants,\n"
                   "\teffectively exploring and exploiting solution spaces.\n\n"
                   "\tIn the parallel version, we employed two approaches within\n"
                   "\tthe same algorithm based on the size of the input data:\n"
                   "\t\t1) If the graph size exceeds 50, additional computation threads "
                   "are utilized.\n"
                   "\t\t2) If the graph size is less than 50, we employ parallel "
                   "computation"
                   "using the `<execution> -> std::execution::par` library.\n\n"
                   "\tIrrespective of the graph size, ants are created in parallel\n"
                   "\tin the parallel algorithm to expedite their creation time.\n";
        std::cout << red << "Thank you for attention\n" << reset << std::endl << '\n';
    }

    void AntView::ConfirmProgramState() {
        std::cout << "Do you want to see adjacency matrix in graph debug? (0/1): ";
        std::cin >> need_print_matrix_;
        auto mode = static_cast<GraphDebugMode>(need_print_matrix_);

        controller_->setGraphDebugMode(mode);

        std::cout << "Do you want to see the best ant path of algorithm? (0/1): ";
        std::cin >> need_print_matrix_;
    }
}  // namespace ng
#endif  // ANT_COLONY

#ifdef GAUSS
namespace ng {
    enum class GaussChoice : int {
        kExitProgram,
        kCreateMatrixRandomly,
        kLoadMatrixFromFile,
        kSolveLinearInSequence,
        kSolveLinearInParallel,
        kSolveLinearCompare,
        kShowMatrix,
        kChangeSettings
    };

    void GaussView::Start() {
        DisplayDescription();
        ConfirmProgramState();
        bool stop = false;

        while (!stop) {
            DisplayMenuHead();
            DisplayMenuItems();

            auto choice = static_cast<GaussChoice>(PerformChoice());

            switch (choice) {
                case GaussChoice::kExitProgram:
                    stop = true;
                    break;
                case GaussChoice::kShowMatrix:
                    controller_->DebugMatrix();
                    break;
                case GaussChoice::kCreateMatrixRandomly: {
                    InputUserMatrixCreateData(controller_);
                    break;
                }
                case GaussChoice::kLoadMatrixFromFile:
                    controller_->LoadMatrixFromFile(
                            PerformStringInput("Enter matrix read file path: "));
                    break;
                case GaussChoice::kSolveLinearInSequence:
                    DisplayGaussSolve(
                            controller_->SolveSystemOfLinearAlgebraicEquationsSequence(),
                            "Solving system of linear algebraic equations in sequence");
                    break;
                case GaussChoice::kSolveLinearInParallel:
                    DisplayGaussSolve(
                            controller_->SolveSystemOfLinearAlgebraicEquationsParallel(),
                            "Solving system of linear algebraic equations in parallel");
                    break;
                case GaussChoice::kSolveLinearCompare: {
                    LaunchCompareThenDisplay();
                    break;
                }
                case GaussChoice::kChangeSettings:
                    ConfirmProgramState();
                    break;
                default:
                    std::cout << red << "Error key code!" << reset << std::endl;
                    break;
            }
        }
    }

    void GaussView::DisplayMenuItems() {
        std::cout << red << "1)" << reset << " Create matrix and fill randomly"
                  << std::endl;
        std::cout << red << "2)" << reset << " Load matrix from file" << std::endl;
        std::cout << red << "3)" << reset
                  << " Solve system of linear algebraic equations in sequence"
                  << std::endl;
        std::cout << red << "4)" << reset
                  << " Solve system of linear algebraic equations in parallel"
                  << std::endl;
        std::cout << red << "5)" << reset
                  << " Compare parallel and sequence realizations" << std::endl;
        std::cout << red << "6)" << reset << " Show current matrix" << std::endl;
        std::cout << red << "7)" << reset << " Change settings" << std::endl;
        DisplayMenuExit();
    }

    void GaussView::DisplayGaussSolve(const GaussTimed &gauss_timed,
                                      std::string_view message) {
        auto [gauss, time_ms] = gauss_timed;
        std::cout << blue << message << reset << std::endl;

        if (need_print_matrix_ and gauss.size() <= top_border_print_) {
            for (std::size_t i = 0; i != gauss.size(); ++i) {
                if (i != 0 and i % 5 == 0) std::cout << '\n';

                std::string str =
                        "x" + std::to_string(i + 1) + " = " + std::to_string(gauss[i]);
                std::cout << blue << std::setw(20) << str;
            }
        }
        std::cout << '\n'
                  << reset << "Solving time is (ms): " << blue << time_ms << reset
                  << std::endl;
    }

    void GaussView::LaunchCompareThenDisplay() {
        int launches_count = PerformIntInput("Enter launches count: ");

        if (launches_count <= 0) {
            std::cout << red << "Launches count mush be at least one!" << reset
                      << std::endl;
            return;
        }

        double sequence_time_ms = 0, parallel_time_ms = 0;

        for (int i = 0; i != launches_count; ++i) {
            sequence_time_ms +=
                    controller_->SolveSystemOfLinearAlgebraicEquationsSequence().second;
            parallel_time_ms +=
                    controller_->SolveSystemOfLinearAlgebraicEquationsParallel().second;
        }

        DisplayCompare(sequence_time_ms, parallel_time_ms, launches_count);
    }

    void GaussView::DisplayDescription() {
        std::cout << red << "Copyright School21 Students: Tonitaga | Manhunte"
                  << reset << std::endl;
        std::cout << std::endl;
        std::cout << green << "Description:" << reset << std::endl;
        std::cout
                << "\tThe Gauss Algorithm, also known as the Gauss Method, is an "
                   "alternative way\n"
                   "\tto solve a system of linear algebraic equations.\n\n"
                   "\tThe advantage of this method is its simplicity,\n"
                   "\tas it only requires a piece of paper and knowledge of addition and "
                   "subtraction.\n\n"
                   "\tTo implement parallel calculations, we have used OpenMP "
                   "directives,\n"
                   "\tspecifically parallelization of the main for loop using the "
                   "'#pragma omp parallel for' directive.\n\n"
                   "\tIt is well-known that parallel computation can be costly,\n"
                   "\tso sequential computation will be faster for small data sizes.\n"
                   "\tTo observe the performance, create a matrix with sizes starting "
                   "from 250.\n";
        std::cout << red << "Thank you for attention\n" << reset << std::endl << '\n';
    }

    void GaussView::ConfirmProgramState() {
        std::cout << "Do you want to see roots of linear algebraic equation? (0/1): ";
        std::cin >> need_print_matrix_;

        if (!need_print_matrix_) return;

        std::cout << "Enter the top border of printing roots (Example: 100): ";
        std::cin >> top_border_print_;
    }
}  // namespace ng
#endif  // GAUSS

#ifdef WINOGRAD
namespace ng {
    enum class WinogradChoice : int {
        kExitProgram,
        kCreateMatricesRandomly,
        kReadMatricesFromFile,
        kMulMatricesSimple,
        kMulMatricesUsingThreads,
        kMulMatricesUsingPipelineParallelism,
        kMulMatricesNaive,
        kMulMatricesCompare,
        kShowMatrices,
        kChangeSettings
    };

    void WinogradView::Start() {
        DisplayDescription();
        ConfirmProgramState();
        bool stop = false;

        while (!stop) {
            DisplayMenuHead();
            DisplayMenuItems();

            auto choice = static_cast<WinogradChoice>(PerformChoice());

            switch (choice) {
                case WinogradChoice::kExitProgram:
                    stop = true;
                    break;
                case WinogradChoice::kShowMatrices:
                    if (need_print_matrix_) controller_->DebugMatrices();
                    break;
                case WinogradChoice::kReadMatricesFromFile:
                    controller_->LoadMatricesFromFile(
                            PerformStringInput("Enter first matrix read file path: "),
                            PerformStringInput("Enter second matrix read file path: "));
                    break;
                case WinogradChoice::kCreateMatricesRandomly: {
                    InputUserMatrixCreateData(controller_);
                    break;
                }
                case WinogradChoice::kMulMatricesSimple:
                    DisplayWinogradSolve(controller_->MulMatricesSimple(),
                                         "Simple one thread winograd algorithm: ");
                    break;
                case WinogradChoice::kMulMatricesUsingThreads: {
                    int threads_count = getThreadsCount();
                    if (threads_count == -1) continue;

                    DisplayWinogradSolve(
                            controller_->MulMatricesUsingThreads(threads_count),
                            "Parallel computation of winograd algorithm: ");
                    break;
                }
                case WinogradChoice::kMulMatricesUsingPipelineParallelism: {
                    int threads_count = getThreadsCount();
                    if (threads_count == -1) continue;

                    DisplayWinogradSolve(
                            controller_->MullMatricesUsingPipelineParallelism(threads_count),
                            "Pipeline Parallelism computation of winograd algorithm: ");
                    break;
                }
                case WinogradChoice::kMulMatricesNaive:
                    DisplayWinogradSolve(controller_->MulMatricesNaive(),
                                         "Simple one thread naive algorithm: ");
                    break;
                case WinogradChoice::kMulMatricesCompare:
                    LaunchCompareThenDisplay();
                    break;
                case WinogradChoice::kChangeSettings:
                    ConfirmProgramState();
                    break;
                default:
                    std::cout << red << "Error key code!" << reset << std::endl;
                    break;
            }
        }
    }

    void WinogradView::DisplayMenuItems() {
        std::cout << red << "1)" << reset << " Create matrices and fill randomly"
                  << std::endl;
        std::cout << red << "2)" << reset << " Load matrices from file" << std::endl;
        std::cout << red << "3)" << reset << " Multiply matrices simple in one thread"
                  << std::endl;
        std::cout << red << "4)" << reset
                  << " Multiply matrices in more that one thread" << std::endl;
        std::cout << red << "5)" << reset
                  << " Multiply matrices using pipeline parallelism" << std::endl;
        std::cout << red << "6)" << reset << " Multiply matrices naive" << std::endl;
        std::cout << red << "7)" << reset << " Compare 3-6 parts" << std::endl;
        std::cout << red << "8)" << reset << " Show matrices" << std::endl;
        std::cout << red << "9)" << reset << " Change settings" << std::endl;
        DisplayMenuExit();
    }

    void WinogradView::DisplayWinogradSolve(const WinogradTimed &winograd_timed,
                                            std::string_view message) {
        auto [matrix, time_ms] = winograd_timed;
        if (matrix.isSquare() and matrix.getRows() == 0) return;

        std::cout << blue << message << reset << std::endl;

        if (need_print_matrix_ and matrix.getRows() <= top_border_print_) {
            std::cout << "Multiplied matrix: " << std::endl;
            std::cout << blue << matrix << reset << std::endl << std::endl;
        }
        std::cout << "Solving time is (ms): " << blue << time_ms << reset
                  << std::endl;
    }

    void WinogradView::LaunchCompareThenDisplay() {
        int launches_count = PerformIntInput("Enter launches count: ");

        if (launches_count <= 0) {
            std::cout << red << "Launches count mush be at least one!" << reset
                      << std::endl;
            return;
        }

        int threads_count = getThreadsCount();
        if (threads_count == -1) return;

        double sequence_time_ms1 = 0, sequence_time_ms2 = 0, parallel_time_ms = 0,
                pipeline_time_ms = 0;
        for (int i = 0; i != launches_count; ++i) {
            sequence_time_ms1 += controller_->MulMatricesSimple().second;
            sequence_time_ms2 += controller_->MulMatricesNaive().second;
            parallel_time_ms +=
                    controller_->MulMatricesUsingThreads(threads_count).second;
            pipeline_time_ms +=
                    controller_->MullMatricesUsingPipelineParallelism(threads_count).second;
        }

        DisplayCompare(sequence_time_ms1, sequence_time_ms2, parallel_time_ms,
                       pipeline_time_ms, launches_count);
    }

    void WinogradView::DisplayDescription() {
        std::cout << red << "Copyright School21 Students: Tonitaga | Manhunte"
                  << reset << std::endl;
        std::cout << std::endl;
        std::cout << green << "Description:" << reset << std::endl;
        std::cout
                << "\tThe Winograd algorithm is an optimized matrix multiplication\n"
                   "\tmethod that was proposed by Winograd\n\n"
                   "\tThis algorithm is based on the observation that some calculations\n"
                   "\tin a standard matrix multiplication algorithm can be performed\n"
                   "\tin advance and their results can be reused to reduce the number of "
                   "operations.\n\n";
        std::cout << red << "Thank you for attention\n" << reset << std::endl << '\n';
    }

    int WinogradView::getThreadsCount() {
        std::size_t max_threads = std::thread::hardware_concurrency();
        std::cout << red
                  << "Max possible using threads in this hardware is: " << max_threads
                  << reset << std::endl;
        std::size_t threads_count = PerformIntInput("Enter mod 2 count of threads: ");

        if (threads_count > max_threads or threads_count % 2 != 0) {
            std::cout << red << "Invalid input!" << reset << std::endl;
            return -1;
        }

        return threads_count;
    }

    void WinogradView::ConfirmProgramState() {
        std::cout << "Do you want to see multiplied matrix at output? (1/0): ";
        std::cin >> need_print_matrix_;

        if (!need_print_matrix_) return;

        std::cout << "Enter top border of printing (Example: 200): ";
        std::cin >> top_border_print_;
    }
}  // namespace ng
#endif  // WINOGRAD

namespace ng {
    BaseView &getViewInstance(Controller *controller) {
#ifdef ANT_COLONY
        static AntView view(controller);
#endif
#ifdef GAUSS
        static GaussView view(controller);
#endif
#ifdef WINOGRAD
        static WinogradView view(controller);
#endif
        return view;
    }
}  // namespace ng
