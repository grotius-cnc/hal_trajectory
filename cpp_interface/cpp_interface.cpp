#include "cpp_interface.h"

ruckig::Ruckig<6> otg {0.001};
ruckig::InputParameter<6> input;
ruckig::OutputParameter<6> output;

Cpp_interface::Cpp_interface()
{
}

void Cpp_interface::trajectory_init(data d){
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

    auto result = otg.update(input, output);
    result = ruckig::Result::Working;
}

double Cpp_interface::trajectory_time(){
    return output.trajectory.get_duration();
}

pos Cpp_interface::trajectory_at_time(double at_time){
    std::array<double, 6> new_position, new_velocity, new_acceleration;
    output.trajectory.at_time(at_time, new_position, new_velocity, new_acceleration);

    //! Copy cplusplus array style data to c style array data
    pos p;
    for(unsigned int i=0; i<6; i++){
        p.position[i]=new_position.at(i);
        p.velocity[i]=new_velocity.at(i);
        p.acceleration[i]=new_acceleration.at(i);
    }
    return p;
}

void Cpp_interface::example(data d){

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

    auto result = otg.update(input, output);
    result = ruckig::Result::Working;
    std::array<double, 6> new_position, new_velocity, new_acceleration;
    output.trajectory.at_time(output.trajectory.get_duration(), new_position, new_velocity, new_acceleration);

    for(unsigned int i=0; i<6; i++){
        std::cout<<"new_position:"<<new_position.at(i)<<std::endl;
        std::cout<<"new_velocity:"<<new_velocity.at(i)<<std::endl;
        std::cout<<"new_acceleration:"<<new_acceleration.at(i)<<std::endl;
    }
}

// C module function wrappers:
extern "C" void wrapper_example(struct data d){ // C to cpp wrapper function
    Cpp_interface().example(d);
}

extern "C" void wrapper_trajectory_init(struct data d){ // C to cpp wrapper function
    Cpp_interface().trajectory_init(d);
}

extern "C" double wrapper_trajectory_time(){ // C to cpp wrapper function
    double time=Cpp_interface().trajectory_time();
    return time;
}

extern "C" pos wrapper_trajectory_at_time(double at_time){ // C to cpp wrapper function
    pos p=Cpp_interface().trajectory_at_time(at_time);
    return p;
}





