#include <iostream>

#include "views.h"

int main() {
    s21::Model model;
    s21::Controller controller(&model);
    s21::getViewInstance(&controller).Start();
    return EXIT_SUCCESS;
}
