#ifndef HALMODULE_H
#define HALMODULE_H

#include <stdio.h>
#include <stdbool.h>

//! A struct that represent a 3d point.
struct POINT {
double x,y,z;
};

struct TCP {
    struct POINT p;
    double vel,acc,jerk;
};

// C module functions:
extern void wrapper_load_gcode();
extern struct TCP wrapper_trajectory(double vel, double acc, double jerk, unsigned int startfromblock, double tcp_x, double tcp_y, double tcp_z);

#endif // HALMODULE_H
