#ifndef A3_PARALLELS_VIEW_VIEWS_H_
#define A3_PARALLELS_VIEW_VIEWS_H_

#include "base_view.h"
#include "controller.h"

#ifdef ANT_COLONY
namespace ng {
    class AntView final : public BaseView {
    public:
        explicit AntView(Controller *controller) : controller_(controller) {};

        void Start() override;

    private:
        void DisplayMenuItems() override;
        void DisplayDescription() override;

        void DisplayAntColonySolve(const AntColonyTimed &ant_timed,
                                   std::string_view message);

        void LaunchCompareThenDisplay();
        void ConfirmProgramState();

        std::size_t top_border_print_ = 0;
        bool need_print_matrix_ = true;

        Controller *controller_;
    };
}  // namespace ng
#endif  // ANT_COLONY

#ifdef GAUSS
namespace ng {
    class GaussView final : public BaseView {
    public:
        explicit GaussView(Controller *controller) : controller_(controller) {};

        void Start() override;

    private:
        void DisplayMenuItems() override;
        void DisplayDescription() override;
        void DisplayGaussSolve(const GaussTimed &gauss_timed,
                               std::string_view message);

        void LaunchCompareThenDisplay();
        void ConfirmProgramState();

        std::size_t top_border_print_ = 0;
        bool need_print_matrix_ = true;

        Controller *controller_;
    };
}  // namespace ng
#endif  // GAUSS

#ifdef WINOGRAD
namespace ng {
    class WinogradView final : public BaseView {
    public:
        explicit WinogradView(Controller *controller) : controller_(controller) {};

        void Start() override;

    private:
        void DisplayMenuItems() override;
        void DisplayDescription() override;
        void DisplayWinogradSolve(const WinogradTimed &winograd_timed,
                                  std::string_view message);
        void LaunchCompareThenDisplay();

        int getThreadsCount();

        void ConfirmProgramState();

        std::size_t top_border_print_ = 0;
        bool need_print_matrix_ = true;

        Controller *controller_;
    };
}  // namespace ng
#endif  // WINOGRAD

namespace ng {
    BaseView &getViewInstance(Controller *controller);
}

#endif  // A3_PARALLELS_VIEW_VIEWS_H_
