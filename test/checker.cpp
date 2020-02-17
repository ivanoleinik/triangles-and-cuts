#include <cmath>

#include "geom.h"
#include "checker.h"

bool orth(Segment s, Segment side) {
    return fabs((s.p2 - s.p1) * (side.p2 - side.p1)) < EPS;
}

bool in_half(Segment s, Point p) {
    double half1 = (p - s.p1).length();
    double half2 = (p - s.p2).length();
    return fabs(half1 - half2) < EPS;
}

Side good_seg(Triangle t, Segment s, double l) {
    Point A(t.A), B(t.B), C(t.C);
    Segment AB(A, B), BC(B, C), CA(C, A);

    if (fabs(s.length() - l) > EPS)
        return ERROR;

    Point p;
    Side side = ERROR;
    int num_of_intersections = 0;
    if (intersection(AB, s, p) != -1) {
        num_of_intersections++;
        side = SIDE_AB;
        if (!in_half(s, p) || !orth(s, AB))
            return ERROR;
    }
    if (intersection(BC, s, p) != -1) {
        num_of_intersections++;
        side = SIDE_BC;
        if (!in_half(s, p) || !orth(s, BC))
            return ERROR;
    }
    if (intersection(CA, s, p) != -1) {
        num_of_intersections++;
        side = SIDE_CA;
        if (!in_half(s, p) || !orth(s, CA))
            return ERROR;
    }

    if (num_of_intersections != 1)
        return ERROR;
    return side;
}

bool checker(Triangle t, Triple triple, double l) {
    Segment s1(triple.first), s2(triple.second), s3(triple.third);

    Point p;
    if (intersection(s1, s2, p) != -1 ||
        intersection(s2, s3, p) != -1 ||
        intersection(s3, s1, p) != -1) {
        return false;
    }

    if (good_seg(t, s1, l) * good_seg(t, s2, l) * good_seg(t, s3, l) != 6) {
        return false;
    }

    return true;
}