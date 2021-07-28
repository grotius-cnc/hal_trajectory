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

extern void function(struct data d);

#endif // HALMODULE_H
