#include <iostream>

#include "views.h"

int main() {
    ng::Model model;
    ng::Controller controller(&model);
    ng::getViewInstance(&controller).Start();
    return EXIT_SUCCESS;
}
