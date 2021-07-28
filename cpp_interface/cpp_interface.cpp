#include "cpp_interface.h"

ruckig::Ruckig<6> otg {0.001};
ruckig::InputParameter<6> input;
ruckig::OutputParameter<6> output;

Cpp_interface::Cpp_interface()
{
}

void Cpp_interface::calculate(data d){

    //! Create instances: the ruckig otg as well as input and output parameters
    //! Convert c style array data to cplusplus style data.
    for(unsigned int i=0; i<6; i++){
        input.max_velocity[i]=d.max_velocity[i];
        input.max_acceleration[i]=d.max_acceleration[i];
        input.max_jerk[i]=d.max_jerk[i];
        input.current_position[i]=d.current_position[i];
        input.current_velocity[i]=d.current_velocity[i];
        input.current_acceleration[i]=d.current_acceleration[i];
        input.target_position[i]=d.target_position[i];
        input.target_velocity[i]=d.target_velocity[i];
        input.target_acceleration[i]=d.target_acceleration[i];
    }

    // Generate trajectory
    std::cout << "t | p1 | p2 | p3 | p4 | p5 | p6" << std::endl;
    while (otg.update(input, output) == ruckig::Result::Working) {
        auto& p = output.new_position;
        std::cout << output.time << " " << p[0] << " " << p[1] << " " << p[2] << " " << p[3] << " " << p[4] << " " << p[5] << std::endl;

        input.current_position = output.new_position;
        input.current_velocity = output.new_velocity;
        input.current_acceleration = output.new_acceleration;
    }

    std::cout << "Reached target position in " << output.trajectory.get_duration() << " [s]." << std::endl;
}

// C module function wrappers:
extern "C" void function(struct data d){ // C to cpp wrapper function
    Cpp_interface().calculate(d);
}
