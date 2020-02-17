#include <iostream>

#include "show.h"

void show(Triple triple) {
    std::cout << "\nOne of the ways:\n" << std::endl;

    std::cout << "first cut: ";
    triple.first.show();

    std::cout << "second cut: ";
    triple.second.show();

    std::cout << "third cut: ";
    triple.third.show();

    std::cout << std::endl;
    return;
}