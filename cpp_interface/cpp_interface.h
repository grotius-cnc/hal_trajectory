#ifndef CPP_INTERFACE_H
#define CPP_INTERFACE_H

// https://github.com/pantor/ruckig

#include "cpp_interface_global.h"
#include <iostream>
#include <ruckig.hpp>

// c module variables:
struct data {
    double max_velocity[6];
    double max_acceleration[6];
    double max_jerk[6];
    double current_position[6];
    double current_velocity[6];
    double current_acceleration[6];
    double target_position[6];
    double target_velocity[6];
    double target_acceleration[6];
};

struct pos {
    double position[6];
    double velocity[6];
    double acceleration[6];
};

class CPP_INTERFACE_EXPORT Cpp_interface
{
public:
    Cpp_interface();

    void example(data d);
    void trajectory_init(data d);
    double trajectory_time();
    pos trajectory_at_time(double at_time);

    // C module functions:
    void wrapper_example(struct data d);
    void wrapper_trajectory_init(struct data d);
    double wrapper_trajectory_time();
    pos wrapper_trajectory_at_time(double at_time);

};

#endif // CPP_INTERFACE_H
