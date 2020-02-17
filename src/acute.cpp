#include <cmath>

#include "geom.h"
#include "show.h"
#include "acute.h"

double expr1(double phi, double psi, double l) {
    return l * (1 / tan(phi) + 1 / sin(psi)) / 2.0;
}

bool case1(Triangle t, double l) {
    double alpha = t.alpha(), beta = t.beta(), gamma = t.gamma();
    return t.AB() - expr1(alpha, beta, l) > EPS &&
           t.BC() - expr1(beta, gamma, l) > EPS &&
           t.CA() - expr1(gamma, alpha, l) > EPS;
}

Segment way1_cut(Segment s, double phi, double l) {
    Point cut_center;

    double p1_to_cut_center = l / (2.0 * tan(phi));
    double ratio = p1_to_cut_center / (s.length() - p1_to_cut_center);
    divide_seg_in_ratio(s, ratio, cut_center);

    return build_cut(s, cut_center, l);
}

Triple way1(Triangle t, double l) {
    Point A = t.A, B = t.B, C = t.C;
    Segment AB(A, B), BC(B, C), CA(C, A);
    double alpha = t.alpha(), beta = t.beta(), gamma = t.gamma();

    return Triple(
            way1_cut(AB, alpha, l),
            way1_cut(BC, beta, l),
            way1_cut(CA, gamma, l)
    );
}

double case2(Triangle t, double l) {
    return t.AB() - l * (1 / sin(t.alpha()) + 1 / sin(t.beta())) / 2.0 > EPS;
}

Triple way2(Triangle t, double l) {
    Point A = t.A, B = t.B, C = t.C;
    Segment AB(A, B), BC(B, C), CA(C, A);
    double alpha = t.alpha(), beta = t.beta();
    double a = t.BC(), b = t.CA(), c = t.AB();

    Point cut_center_AB, cut_center_BC, cut_center_CA;

    divide_seg_in_ratio(AB, b / a, cut_center_AB);

    double B_to_cut_center_BC = a * c * cos(beta) / (a + b);
    double ratio_BC = B_to_cut_center_BC / (a - B_to_cut_center_BC);
    divide_seg_in_ratio(BC, ratio_BC, cut_center_BC);

    double A_to_cut_center_CA = b - b * c * cos(alpha) / (a + b);
    double ratio_CA = (b - A_to_cut_center_CA) / A_to_cut_center_CA;
    divide_seg_in_ratio(CA, ratio_CA, cut_center_CA);

    return Triple(
            build_cut(AB, cut_center_AB, l),
            build_cut(BC, cut_center_BC, l),
            build_cut(CA, cut_center_CA, l)
    );
}

Triple solve_acute(Triangle t, double l) {
    Point A = t.A, B = t.B, C = t.C;
    Segment AB(A, B), BC(B, C), CA(C, A);

    if (!t.is_acute())
        throw GeomException("The triangle is not acute!");

    Triangle t2 = Triangle(A, C, B),
            t3 = Triangle(B, C, A),
            t4 = Triangle(C, A, B);

    if (case1(t, l))
        return way1(t, l);
    if (case1(t2, l))
        return way1(t2, l);
    if (case2(t, l))
        return way2(t, l);
    if (case2(t3, l))
        return way2(t3, l);
    if (case2(t4, l))
        return way2(t4, l);

    throw GeomException("Unable to fulfill the required.");
}