#ifndef HALMODULE_H
#define HALMODULE_H

#include <stdio.h>
#include <stdbool.h>

// In the makefile the external so lib has to be present with -L/path -llibname
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

// C module functions:
extern void wrapper_example(struct data d);
extern void wrapper_trajectory_init(struct data d);
extern double wrapper_trajectory_time();
extern struct pos wrapper_trajectory_at_time(double at_time);

#endif // HALMODULE_H
