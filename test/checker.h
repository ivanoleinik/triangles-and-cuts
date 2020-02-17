#ifndef CHECKER_H
#define CHECKER_H

enum Side {
    ERROR, // 0
    SIDE_AB,    // 1
    SIDE_BC,    // 2
    SIDE_CA     // 3
};

bool orth(Segment s, Segment side);

bool in_half(Segment s, Point p);

Side good_seg(Triangle t, Segment s, double l);

bool checker(Triangle t, Triple triple, double l);

#endif