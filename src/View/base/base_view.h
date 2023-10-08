#ifndef A3_PARALLELS_VIEW_BASE_BASE_VIEW_H_
#define A3_PARALLELS_VIEW_BASE_BASE_VIEW_H_

#include <mutex>

#include "controller.h"
#include "termcolor.h"

using namespace termcolor;

namespace s21 {
    class BaseView {
    public:
        virtual void Start();

        BaseView() noexcept = default;
        BaseView(const BaseView &) = delete;
        BaseView &operator=(const BaseView &) = delete;

    protected:
        virtual void DisplayMenuHead();
        virtual void DisplayMenuItems();
        virtual void DisplayMenuExit();
        virtual void DisplayDescription();

        void InputUserMatrixCreateData(Controller *controller);

        int PerformChoice(std::string_view message = "Input a menu item digit: ",
                          std::string_view error_message = "Input Error, try again.");
        int PerformIntInput(std::string_view message);
        double PerformFloatingInput(std::string_view message);
        std::string PerformStringInput(std::string_view message);

        std::mutex mutex_;

        void DisplayCompare(double single_ms, double multi_ms, int launches_count,
                            std::ostream &out = std::cout);
        void DisplayCompare(double single_ms1, double single_ms2, double multi_ms,
                            double pipeline_ms, int launches_count,
                            std::ostream &out = std::cout);
    };
}  // namespace s21

#endif  // A3_PARALLELS_VIEW_BASE_BASE_VIEW_H_
