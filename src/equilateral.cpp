#include <iostream>

#include "geom.h"
#include "equilateral.h"
#include "show.h"

Segment cut(Segment s, double l) {
    Point cut_center;

    divide_seg_in_ratio(s, 2.0, cut_center);

    return build_cut(s, cut_center, l);
}

Triple solve_equilateral(Triangle t, double l) {
    Point A = t.A, B = t.B, C = t.C;
    Segment AB(A, B), BC(B, C), CA(C, A);

    if (!t.is_equilateral())
        throw GeomException("The triangle is not equilateral!");
    if (AB.length() - sqrt(3.0) * l / 2.0 < EPS)
        throw GeomException("Unable to fulfill the required.");
    else {
        return Triple(cut(AB, l), cut(BC, l), cut(CA, l));
    }
}
