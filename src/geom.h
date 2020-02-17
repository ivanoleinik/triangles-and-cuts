#ifndef GEOM_H
#define GEOM_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <exception>
#include <cmath>

const double EPS = 1e-7;

class GeomException : public std::exception {
public:
    GeomException(std::string msg) : std::exception() { _msg = msg; }

    const char *what() const noexcept { return _msg.c_str(); }

private:
    std::string _msg;
};

struct Vector {
    double x, y;

    Vector() : x(0.0), y(0.0) {};

    Vector(double x, double y) : x(x), y(y) {};

    double length();

    // return -1 if the vector is 0
    int normalize();

    Vector rotate90(); // counterclockwise
    Vector rotate180();

    Vector rotate270(); // clockwise

    Vector operator-(Vector v);

    Vector operator+(Vector v);

    Vector operator*(double sc);

    double dist(Vector v);

    double operator*(Vector v);

    double operator^(Vector v);

    void show();
};

typedef Vector Point;

struct Line {
    Point p1, p2;

    Line(Point p1, Point p2) : p1(p1), p2(p2) {};

    double coef_a(), coef_b(), coef_c();
};

struct Segment {
    Point p1, p2;

    Segment(Point p1, Point p2) : p1(p1), p2(p2) {};

    double length();

    void show();
};

struct Triple {
    Segment first, second, third;

    Triple(Segment first, Segment second, Segment third) :
            first(first), second(second), third(third) {};
};

struct Triangle {
    Point A, B, C;

    Triangle(Point A, Point B, Point C) : A(A), B(B), C(C) {};

    double AB(), BC(), CA(); // side lengths getters
    double alpha(), beta(), gamma(); // angle measures getters

    bool is_equilateral();

    bool is_acute();
};

// return -1 if two lines are parallel
int intersection(Line ln1, Line ln2, Point &p);

// return -1 if two segments do not intersect
int intersection(Segment s1, Segment s2, Point &p);

// return -1 if ratio is 0
int divide_seg_in_ratio(Segment s, double rat, Point &p);

// return 1 if point is on the segment
//        0 if not on the line
//       -1 if on the line but not on the segment
int seg_and_pt(Segment s, Point p);

// angle from p1->p2 to p1->p3, returns -PI to PI
double angle(Point p1, Point p2, Point p3);

// in a triangle with sides a,b,c, the angle between b and c
// in assumption that such triangle exists
double angle(double a, double b, double c);

// rotate p1 around p0 clockwise, by angle a
void rotate(Point p0, Point p1, double a, Point &p1_rot);

void reflect(Line &ln, Point p, Point &p_refl);

Segment build_cut(Segment s, Point cut_center, double l);

#endif
