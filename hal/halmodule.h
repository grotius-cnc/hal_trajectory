#ifndef HALMODULE_H
#define HALMODULE_H

#include <stdio.h>
#include <stdbool.h>

//! A struct that represent a 3d point.
struct POINT {
    double x,y,z;
};

//! A struct that represents a direction vector.
struct EULER{
    double euler_x, euler_y, euler_z;
};

struct TCP {
    struct POINT p;
    struct EULER e;
    double vel,acc,jerk,pos;
    bool m3,m7,m8;
    double power_rpm;
};
struct TCP tcp;

// C module functions:
extern void wrapper_load_gcode();
//! Mode auto.
extern struct TCP wrapper_trajectory_auto(double velocity_override,
                                          bool start, bool stop, bool pause, bool resume,
                                          double vel, double acc, double jerk,
                                          unsigned int startfromblock, double tcp_x, double tcp_y, double tcp_z);

//! Mode jog. jog_x = 1 (positive move) )or -1 (negative move)
extern struct TCP wrapper_trajectory_jog(int jog_x, int jog_y, int jog_z,
                                         int jog_euler_x, int jog_euler_y, int jog_euler_z,
                                         double vel, double acc, double jerk,
                                         double tcp_x, double tcp_y, double tcp_z,
                                         double tcp_euler_x, double tcp_euler_y, double tcp_euler_z);

#endif // HALMODULE_H
