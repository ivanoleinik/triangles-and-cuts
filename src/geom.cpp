#include <iostream>
#include <iomanip>

#include "geom.h"

double Vector::length() {
    return sqrt(x * x + y * y);
}

int Vector::normalize() {
    double len = length();
    if (fabs(len) < EPS)
        return -1;
    x /= len;
    y /= len;
    return 0;
}

Vector Vector::rotate90() {
    return Vector(-y, x);
}

Vector Vector::rotate180() {
    return Vector(-x, y);
}

Vector Vector::rotate270() {
    return Vector(y, -x);
}


Vector Vector::operator-(Vector v) {
    return Vector(x - v.x, y - v.y);
}

Vector Vector::operator+(Vector v) {
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator*(double sc) {
    return Vector(x * sc, y * sc);
}

double Vector::dist(Vector v) {
    return sqrt((x - v.x) * (x - v.x) +
                (y - v.y) * (y - v.y));
}

double Vector::operator*(Vector v) {
    return x * v.x + y * v.y;
}

double Vector::operator^(Vector v) {
    return x * v.y - y * v.x;
}

void Vector::show() {
    std::cout << std::fixed << std::setprecision(7) << "(" << x << ", " << y << ")" << std::endl;
    return;
}

double Line::coef_a() {
    return p1.y - p2.y;
}

double Line::coef_b() {
    return p1.x - p1.x;
}

double Line::coef_c() {
    return p1.x * p2.y - p1.y * p2.x;
}

double Segment::length() {
    return (p1 - p2).length();
}

void Segment::show() {
    std::cout << std::fixed << std::setprecision(7) << "(" <<
              p1.x << ", " << p1.y << ")  ---  (" <<
              p2.x << ", " << p2.y << ")" << std::endl;
    return;
}

double Triangle::AB() {
    return A.dist(B);
}

double Triangle::BC() {
    return B.dist(C);
}

double Triangle::CA() {
    return C.dist(A);
}

double Triangle::alpha() {
    return angle(BC(), CA(), AB());
}

double Triangle::beta() {
    return angle(CA(), AB(), BC());
}

double Triangle::gamma() {
    return angle(AB(), BC(), CA());
}

bool Triangle::is_equilateral() {
    return fabs(AB() - BC()) < EPS && fabs(BC() - CA()) < EPS;
}

bool Triangle::is_acute() {
    return M_PI - std::max(alpha(), std::max(beta(), gamma())) > EPS;
}

int intersection(Line ln1, Line ln2, Point &p) {
    Point p1 = ln1.p1, p2 = ln1.p2, p3 = ln2.p1, p4 = ln2.p2;

    double d = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
    if (fabs(d) < EPS)
        return -1;
    double sc = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / d;
    p = p1 + (p2 - p1) * sc;
    return 0;
}

int intersection(Segment s1, Segment s2, Point &p) {
    Line ln1(s1.p1, s1.p2), ln2(s2.p1, s2.p2);
    if (intersection(ln1, ln2, p) == -1)
        return -1;

    if (seg_and_pt(s1, p) != 1 || seg_and_pt(s2, p) != 1)
        return -1;
    return 0;
}

int divide_seg_in_ratio(Segment s, double rat, Point &p) {
    if (fabs(rat) < EPS)
        return -1;
    p.x = (s.p1.x + s.p2.x * rat) / (rat + 1.0);
    p.y = (s.p1.y + s.p2.y * rat) / (rat + 1.0);
    return 0;
}

int seg_and_pt(Segment s, Point p) {
    Vector v1 = s.p1 - p, v2 = s.p2 - p;

    double area2 = fabs(v1 ^ v2);
    if (area2 > EPS)
        return 0;
    if (v1 * v2 > -EPS)
        return -1;
    return 1;
}

double angle(Point p1, Point p2, Point p3) {
    Vector v1 = (p2 - p1);
    v1.normalize();
    Vector v2(-v1.y, v1.x);
    Vector v = p3 - p1;
    return atan2(v * v2, v * v1);
}

double angle(double a, double b, double c) {
    return acos((b * b + c * c - a * a) / (2.0 * b * c));
}

void rotate(Point p0, Point p1, double a, Point &p1_rot) {
    p1 = p1 - p0;
    p1_rot.x = cos(a) * p1.x - sin(a) * p1.y;
    p1_rot.y = sin(a) * p1.x + cos(a) * p1.y;
    p1_rot = p1_rot + p0;
    return;
}

void reflect(Line &ln, Point p, Point &p_refl) {
    if (p.dist(ln.p1) < EPS) {
        p_refl = p;
        return;
    }
    p_refl = p;
    rotate(ln.p1, p_refl, -2.0 * angle(ln.p1, ln.p2, p), p_refl);
    return;
}

Segment build_cut(Segment s, Point cut_center, double l) {
    Vector v = s.p2 - s.p1;
    v.normalize();
    v = v * (l / 2.0);

    return Segment(cut_center + v.rotate90(), cut_center + v.rotate270());
}
