#include <iostream>
#include <exception>

#include "geom.h"
#include "equilateral.h"
#include "acute.h"
#include "show.h"

int main(int argc, char **argv) {
    try {
        int action = -1;
        enum {
            SOLVE_EQUILATERAL,
            SOLVE_ACUTE
        };

        if (argc == 2 && !strcmp(argv[1], "-eq")) {
            action = SOLVE_EQUILATERAL;
        } else if (argc == 1) {
            action = SOLVE_ACUTE;
        } else {
            throw GeomException("Bad input!");
        }

        double x1, y1, x2, y2, x3, y3, l;
        try {
            std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> l;
        } catch (...) {
            throw GeomException("Bad input!");
        }

        Point A(x1, y1), B(x2, y2), C(x3, y3);
        Triangle t(A, B, C);

        if (action == SOLVE_EQUILATERAL) {
            show(solve_equilateral(t, l));
        } else if (action == SOLVE_ACUTE) {
            show(solve_acute(t, l));
        } else {
            throw GeomException("Bad action!");
        }

        return 0;
    } catch (GeomException &ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
}
