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

class CPP_INTERFACE_EXPORT Cpp_interface
{
public:
    Cpp_interface();

    void calculate(data d);

    // C module functions:
    void function(struct data d);


};

#endif // CPP_INTERFACE_H
