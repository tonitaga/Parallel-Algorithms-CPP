#include "base_view.h"

#include <limits>

namespace s21 {
    void BaseView::Start() {
        bool stop = false;

        while (!stop) {
            DisplayMenuHead();
            DisplayMenuItems();

            int choice = PerformChoice();

            if (choice == 0) stop = true;
        }
    }

    void BaseView::DisplayMenuHead() {
        std::cout << green << "====================================" << std::endl;
        std::cout << "              M E N U" << std::endl;
        std::cout << "====================================" << reset << std::endl;
    }

    void BaseView::DisplayMenuItems() { DisplayMenuExit(); }

    void BaseView::DisplayMenuExit() {
        std::cout << red << "0)" << reset << " Exit program" << std::endl;
    }

    int BaseView::PerformChoice(std::string_view message,
                                std::string_view error_message) {
        int choice = 0;
        std::cout << green << message << reset;
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << red << error_message << reset << std::endl;
        }
        return choice;
    }

    int BaseView::PerformIntInput(std::string_view message) {
        int number = 0;
        std::cout << blue << message << reset;
        std::cin >> number;
        return number;
    }

    double BaseView::PerformFloatingInput(std::string_view message) {
        double number = 0;
        std::cout << blue << message << reset;
        std::cin >> number;
        return number;
    }

    std::string BaseView::PerformStringInput(std::string_view message) {
        std::string str;
        std::cout << blue << message << reset;
        std::cin >> str;
        return str;
    }

    void BaseView::DisplayCompare(double single_ms, double multi_ms,
                                  int launches_count, std::ostream &out) {
        std::scoped_lock lock(mutex_);
        out << blue << "Compared time result: " << reset << std::endl;
        double single_delta = single_ms / static_cast<double>(launches_count);
        double multi_delta = multi_ms / static_cast<double>(launches_count);

        out << blue << "Mean time (ms) of algorithms in " << launches_count
            << " launches is: " << reset << std::endl;
        out << "\t" << blue << "Sequence: " << reset << single_delta << std::endl;
        out << "\t" << blue << "Parallel: " << reset << multi_delta << std::endl;
    }

    void BaseView::DisplayCompare(double single_ms1, double single_ms2,
                                  double multi_ms, double pipeline_ms,
                                  int launches_count, std::ostream &out) {
        std::scoped_lock lock(mutex_);
        out << blue << "Compared time result: " << reset << std::endl;
        double single_delta1 = single_ms1 / static_cast<double>(launches_count);
        double single_delta2 = single_ms2 / static_cast<double>(launches_count);
        double multi_delta = multi_ms / static_cast<double>(launches_count);
        double pipeline_delta = pipeline_ms / static_cast<double>(launches_count);

        out << blue << "Mean time (ms) of algorithms in " << launches_count
            << " launches is: " << reset << std::endl;
        out << "\t" << blue << "Naive:    " << reset << single_delta2 << std::endl;
        out << "\t" << blue << "Sequence: " << reset << single_delta1 << std::endl;
        out << "\t" << blue << "Parallel: " << reset << multi_delta << std::endl;
        out << "\t" << blue << "Pipeline: " << reset << pipeline_delta << std::endl;
    }

    void BaseView::InputUserMatrixCreateData(Controller *controller) {
        int square = PerformIntInput("Enter matrix square size: ");
        if (square <= 0) return;

        double left = PerformFloatingInput("Enter random left border: ");
        double right = PerformFloatingInput("Enter random right border: ");
        controller->CreateMatrixAndFillRandomly(square, left, right);
    }

    void BaseView::DisplayDescription() {
        std::cout << red << "Copyright School21 Students: Tonitaga | Manhunte"
                  << reset << std::endl;
    }

}  // namespace s21
