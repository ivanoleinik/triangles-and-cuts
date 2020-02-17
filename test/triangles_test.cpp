#include <iostream>
#include <sstream>

#include "show.h"
#include "geom.h"
#include "equilateral.h"
#include "acute.h"
#include "checker.h"
#include "autotest.h"
#include "triangles_test.h"

void TrianglesTest::test_equilateral() {
    Triangle t(Point(0.0, 0.0),
               Point(1.0, 0.0),
               Point(0.5, sqrt(3.0) / 2.0));
    double l = 1.0;

    Triple triple = solve_equilateral(t, l);
    DO_CHECK(checker(t, triple, l));
    DO_CHECK(t.is_acute());

    l = 1.5;
    try {
        solve_equilateral(t, l);
    } catch (GeomException &ex) {
        DO_CHECK(!strcmp(ex.what(), "Unable to fulfill the required."));
    }

    t.C.y = 10.0;
    try {
        solve_equilateral(t, l);
    } catch (GeomException &ex) {
        DO_CHECK(!strcmp(ex.what(), "The triangle is not equilateral!"));
    }

    t = Triangle(Point(-2365.2585757691, -2629.8335417498),
                 Point(2049.2372247405, 3170.0625365794),
                 Point(-5180.8680186571, 4093.1800055558));
    l = 1000.0;
    triple = solve_equilateral(t, l);
    DO_CHECK(checker(t, triple, l));
    return;
}

void TrianglesTest::test_acute() {
    Triangle t(Point(-8.0, -8.0),
               Point(-4.0, 6.0),
               Point(12.0, -6.0));
    double l = 1.0;

    Triple triple = solve_acute(t, l);
    DO_CHECK(checker(t, triple, l));

    l = 10.0;
    try {
        solve_acute(t, l);
    } catch (GeomException &ex) {
        DO_CHECK(!strcmp(ex.what(), "Unable to fulfill the required."));
    }

    t.C.y = 12.0;
    try {
        solve_acute(t, l);
    } catch (GeomException &ex) {
        DO_CHECK(!strcmp(ex.what(), "The triangle is not acute!"));
    }

    t = Triangle(Point(-16340.3522345965, 7106.0404303608),
                 Point(-13656.3986381076, 15269.7326196813),
                 Point(-4635.3323832421, 7366.9803633528));
    l = 2000.0;
    triple = solve_acute(t, l);
    DO_CHECK(good_seg(t, triple.second, l));
    DO_CHECK(checker(t, triple, l));
    return;
}

void TrianglesTest::run_all_tests() {
    test_equilateral();
    test_acute();
    return;
}
