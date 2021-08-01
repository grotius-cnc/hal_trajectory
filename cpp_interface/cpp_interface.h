#ifndef CPP_INTERFACE_H
#define CPP_INTERFACE_H

// https://github.com/pantor/ruckig

#include "cpp_interface_global.h"
#include <iostream>
#include <ruckig.hpp>

//! A struct that represent a 3d point.
struct POINT {
double x,y,z;
};

struct TCP {
    POINT p;
    double vel,acc,jerk;
};


class CPP_INTERFACE_EXPORT Cpp_interface
{
public:
    Cpp_interface();

    void load_gcode();
    TCP trajectory(double vel, double acc, double jerk, unsigned int startfromblock, double tcp_x, double tcp_y, double tcp_z);

    // C module functions:
    void wrapper_load_gcode();
    TCP wrapper_trajectory(double vel, double acc, double jerk, unsigned int startfromblock, double tcp_x, double tcp_y, double tcp_z);
};

#endif // CPP_INTERFACE_H
