#include "cpp_interface.h"

ruckig::Ruckig<1> otg {0.001};
ruckig::InputParameter<1> in;
ruckig::OutputParameter<1> out;
std::array<double, 1> position, velocity, acceleration;
std::array<double, 1> rapid_position, rapid_velocity, rapid_acceleration;

//! A struct that represents a direction vector.
struct EULER{
    double euler_x, euler_y, euler_z;
};

//! Different types of gcode operations.
enum BLOCKTYPE {
    G0,
    G1,
    G2,
    G3
};

//! A block is a chunk of gcode that represents a primitive like a line or arc.
struct BLOCK {
    BLOCKTYPE blocktype=BLOCKTYPE::G0;
    POINT start={0,0,0}, center={0,0,0}, end={0,0,0};
    EULER euler_start={0,0,0}, euler_end={0,0,0};
    //! Calculated line or arc lenght.
    double blocklenght=0;
};
BLOCK rapid; // Used for a rapid G0 move to go to the program start position.

//! A path is a collection of blocks.
struct PATH {
    std::vector<BLOCK> blockvec;
    double pathlenght=0;
};
std::vector<PATH> pathvec;
//! Indicates in wich pathvec the traject is active.
unsigned int pvi=0;
int trigger=0;
bool in_position=0;

//! Defenition helper functions.
double line_lenght(BLOCK line);
double arc_lenght(BLOCK arc);
POINT interpolate_line(BLOCK line, double distancetogo, bool debug);
POINT interpolate_arc(BLOCK arc, double distancetogo, bool debug);

Cpp_interface::Cpp_interface()
{
}

//! Setup a demo traject
void Cpp_interface::load_gcode(){
    PATH path;
    BLOCK l;
    l.blocktype=BLOCKTYPE::G1;
    l.start={0,0,0};
    l.end={200,0,0};
    l.blocklenght=line_lenght(l);
    path.pathlenght+=l.blocklenght;
    path.blockvec.push_back(l);

    l.blocktype=BLOCKTYPE::G1;
    l.start={200,0,0};
    l.end={200,200,0};
    l.blocklenght=line_lenght(l);
    path.pathlenght+=l.blocklenght;
    path.blockvec.push_back(l);

    l.start={200,200,0};
    l.end={0,200,0};
    l.blocklenght=line_lenght(l);
    path.pathlenght+=l.blocklenght;
    path.blockvec.push_back(l);

    l.start={0,200,0};
    l.end={0,0,0};
    l.blocklenght=line_lenght(l);
    path.pathlenght+=l.blocklenght;
    path.blockvec.push_back(l);

    pathvec.push_back(path);
    path.blockvec.clear();
    path.pathlenght=0;
    std::cout<<"pathlenght a:"<<pathvec.back().pathlenght<<std::endl; // Checked ok.

    l.blocktype=BLOCKTYPE::G1;
    l.start={0,0,0};
    l.end={50,0,0};
    l.blocklenght=line_lenght(l);
    path.pathlenght+=l.blocklenght;
    path.blockvec.push_back(l);

    l.blocktype=BLOCKTYPE::G1;
    l.start={50,0,0};
    l.end={50,50,0};
    l.blocklenght=line_lenght(l);
    path.pathlenght+=l.blocklenght;
    path.blockvec.push_back(l);

    l.start={50,50,0};
    l.end={0,50,0};
    l.blocklenght=line_lenght(l);
    path.pathlenght+=l.blocklenght;
    path.blockvec.push_back(l);

    l.start={0,50,0};
    l.end={0,0,0};
    l.blocklenght=line_lenght(l);
    path.pathlenght+=l.blocklenght;
    path.blockvec.push_back(l);

    pathvec.push_back(path);
    path.blockvec.clear();
    path.pathlenght=0;
    std::cout<<"pathlenght b:"<<pathvec.back().pathlenght<<std::endl; // Checked ok.
}

//! Performing a collection of trajects.
//! A traject is a collection of gcode blocks between M3 and M5 or a rapic G0.
//!
//! When the trajectory is running, user can set:
//!     max_velocity, results in forward- or backward path move.
//!     max_acceleration
//!     max_jerk
//!
//! A single traject command can be a :
//!     reset pvi=0;
//!     mdi command.
//!     goto startposition of a certain gcode line.
//!
//! For now reset the trigger every time you perform "run from line"
//!
TCP Cpp_interface::trajectory(double vel, double acc, double jerk, unsigned int startfromblock, double tcp_x, double tcp_y, double tcp_z){

    //! Implement start, stop, pause, resume.
    //! When stop :
    //!     trigger=0, in_position=0
    //!     set vel to 0, to make a controlled dcc stop.
    //! When start :
    //!      Nothing to do.
    //! When pause, resume :
    //!      Maybe toggle the time from 0.001 ms to 0.000 ms.
    TCP tcp;

    if(!trigger){
        // Perform a startsequence from current tcp xyz to start tcp xyz of the gcode block.
        unsigned int nr=0, ii=0, jj=0;
        pvi=0;
        for(unsigned int i=0; i<pathvec.size(); i++){
            double lenght=0;
            ii=i;
            for(unsigned int j=0; j<pathvec.at(i).blockvec.size(); j++){

                if(nr==startfromblock){
                    pvi=i;
                    position[0]=lenght;
                    jj=j;
                    break;
                }
                nr++;
                lenght+=pathvec.at(i).blockvec.at(j).blocklenght;
            }
            if(nr==startfromblock){
                break;
            }
        }
        // std::cout<<"pvi start:"<<pvi<<std::endl;
        // std::cout<<"position start of trajectory:"<<position[0]<<std::endl;

        // Set the current tcp location into the BLOCK rapid.
        rapid.start.x=tcp_x;
        rapid.start.y=tcp_y;
        rapid.start.z=tcp_z;
        // std::cout<<"current tcp x:"<<rapid.start.x<<" y:"<<rapid.start.y<<" z:"<<rapid.start.z<<std::endl;

        // Get the actual xyz position of the gcode start location:
        rapid.end=interpolate_line(pathvec.at(ii).blockvec.at(jj),pathvec.at(ii).blockvec.at(jj).blocklenght,0);
        // std::cout<<"gcode startpoint x:"<<rapid.end.x<<" y:"<<rapid.end.y<<" z:"<<rapid.end.z<<std::endl;

        rapid.blocklenght=line_lenght(rapid);
        // std::cout<<"rapid G0 distance:"<<rapid.blocklenght<<std::endl;

        rapid_position[0]=0;
        rapid_velocity[0];
        rapid_acceleration[0];

        trigger=1;
    }

    if(!in_position && trigger==1){

        in.max_velocity[0]=abs(vel);
        in.max_acceleration[0]=acc;
        in.max_jerk[0]=jerk;
        in.current_position[0]=rapid_position[0];
        in.current_velocity[0]=rapid_velocity[0];
        in.current_acceleration[0]=rapid_acceleration[0];
        in.target_position[0]=rapid.blocklenght;
        in.target_velocity[0]=0;
        in.target_acceleration[0]=0;

        auto result = otg.update(in, out);
        result = ruckig::Result::Working;

        // One ms forward.
        out.trajectory.at_time(0.001, rapid_position, rapid_velocity, rapid_acceleration);

        // If in position, end this function.  double blocklenght=pathvec.at(pvi).blockvec.at(i).blocklenght;
        double distancetogo=rapid.blocklenght-rapid_position[0];
        POINT p=interpolate_line(rapid,distancetogo,0);
        std::cout<<"Moving to program start position p.x: "<<p.x<<" p.y:"<<p.y<<" p.z:"<<p.z<<std::endl;
        tcp.p=p;
        tcp.vel=rapid_velocity[0];
        tcp.acc=rapid_acceleration[0];

        // Forward destiny reached, increment to "next" path, if there is one.
        if(rapid_position[0]==rapid.blocklenght){
            in_position=1;
            // std::cout<<"In program start position"<<std::endl;
        }

        // For info: backward move is not implemented in the go to program startposition move.
        // User can do a
    }

    if(in_position){ // Perform the program in auto mode.

        // Maxvel +/- is forward or backward, like adaptive feed.
        if(vel>0){
            in.target_position[0]=pathvec.at(pvi).pathlenght; // Goto path end.
        }
        if(vel<0){
            in.target_position[0]=0; // Goto path begin.
        }
        if(vel==0){ // Cannot input 0 as value. Create a stop sequence. For emergency a instand stop can be done like : vel=0
            vel=0.0001;
            if(velocity[0]<0.001 && velocity[0]>0.000){
                vel=0;
            }
        }

        in.max_velocity[0]=abs(vel);
        in.max_acceleration[0]=acc;
        in.max_jerk[0]=jerk;
        in.current_position[0]=position[0];
        in.current_velocity[0]=velocity[0];
        in.current_acceleration[0]=acceleration[0];
        in.target_velocity[0]=0;
        in.target_acceleration[0]=0;

        auto result = otg.update(in, out);
        result = ruckig::Result::Working;

        // One ms forward.
        out.trajectory.at_time(0.001, position, velocity, acceleration);

        // Gcode block that is currently in use, output is interpolated xyz position.
        double lenght=0;
        for(unsigned int i=0; i<pathvec.at(pvi).blockvec.size(); i++){
            double begin=lenght;
            lenght+=pathvec.at(pvi).blockvec.at(i).blocklenght;
            double end=lenght;

            if(position[0]>=begin && position[0]<=end){
                // std::cout<<"block i:"<<i<<std::endl;

                double blocklenght=pathvec.at(pvi).blockvec.at(i).blocklenght;
                double blockpos=position[0]-begin; // From 0 to blocklenght.
                double distancetogo=blocklenght-blockpos;

                // Interpolate xyz coordinates of the gcode primitive given the distancetogo.
                POINT p;
                if(pathvec.at(pvi).blockvec.at(i).blocktype==BLOCKTYPE::G0 || pathvec.at(pvi).blockvec.at(i).blocktype==BLOCKTYPE::G1){
                    p=interpolate_line(pathvec.at(pvi).blockvec.at(i),distancetogo,0);
                    std::cout<<"line p.x: "<<p.x<<" p.y:"<<p.y<<" p.z:"<<p.z<<std::endl;
                    tcp.p=p;
                    tcp.vel=velocity[0];
                    tcp.acc=acceleration[0];
                }
                if(pathvec.at(pvi).blockvec.at(i).blocktype==BLOCKTYPE::G2 || pathvec.at(pvi).blockvec.at(i).blocktype==BLOCKTYPE::G3){
                    p=interpolate_arc(pathvec.at(pvi).blockvec.at(i),distancetogo,0);
                    std::cout<<"arc p.x: "<<p.x<<" p.y:"<<p.y<<" p.z:"<<p.z<<std::endl;
                    tcp.p=p;
                    tcp.vel=velocity[0];
                    tcp.acc=acceleration[0];
                }
                break;
            }
        }

        // Forward destiny reached, increment to "next" path, if there is one.
        if(position[0]==pathvec.at(pvi).pathlenght && vel>0){
            if(pvi<pathvec.size()-1){
                pvi++;
                // std::cout<<"end of traject reached, forward velocity, into next path"<<std::endl;

                // Set position to begin of next path.
                position[0]=0;
            }
        }

        // backward destiny reached, decrement to "previous" path, if there is one.
        if(position[0]==0 && vel<0){
            if(pvi>0){
                pvi--;
                // std::cout<<"begin of traject reached, backward velocity, into previous path"<<std::endl;

                // Set position to end of (already previous) path
                position[0]=pathvec.at(pvi).pathlenght;
            }
        }

        // std::cout<<"traject pvi:"<<pvi<<std::endl;
        // std::cout<<"pos:"<<position[0]<<std::endl;
        // std::cout<<"vel:"<<velocity[0]<<std::endl;
        // std::cout<<"acc:"<<acceleration[0]<<std::endl;
    }

    return tcp;
}

//! C module function wrappers:
extern "C" void wrapper_load_gcode(){ // C to cpp wrapper function
    Cpp_interface().load_gcode();
}

extern "C" TCP wrapper_trajectory(double vel, double acc, double jerk, unsigned int startfromblock, double tcp_x, double tcp_y, double tcp_z){ // C to cpp wrapper function
    TCP p=Cpp_interface().trajectory(vel, acc, jerk, startfromblock, tcp_x, tcp_y, tcp_z);
    return p;
}

//! Helper functions
double line_lenght(BLOCK line){
    return sqrt(pow(line.end.x-line.start.x,2)+pow(line.end.y-line.start.y,2)+pow(line.end.z-line.start.z,2));
}

double arc_lenght(BLOCK arc){

    double radius=sqrt(pow(arc.end.x-arc.center.x,2)+pow(arc.end.y-arc.center.y,2)+pow(arc.end.z-arc.center.z,2));
    double diameter=radius*2;
    double circumfence=diameter*M_PI;
    double start_angle, end_angle, arc_angle, arc_lenght;

    if(arc.blocktype==BLOCKTYPE::G2){
        start_angle = atan2(arc.end.y-arc.center.y, arc.end.x-arc.center.x);
        end_angle = atan2(arc.start.y-arc.center.y, arc.start.x-arc.center.x);
    }

    if(arc.blocktype==BLOCKTYPE::G3){
        start_angle = atan2(arc.start.y-arc.center.y, arc.start.x-arc.center.x);
        end_angle = atan2(arc.end.y-arc.center.y, arc.end.x-arc.center.x);
    }

    if(end_angle < start_angle){  //this to avoid the start angle is bigger then the end angle value
        end_angle += 2*M_PI;
    }

    arc_angle=end_angle-start_angle;
    arc_lenght=(arc_angle/(2*M_PI))*circumfence;

    return arc_lenght;
}

POINT interpolate_line(BLOCK line, double distancetogo, bool debug)
{
    double lenght=sqrt(pow(line.end.x-line.start.x,2)+pow(line.end.y-line.start.y,2)+pow(line.end.z-line.start.z,2));
    double ratio=0;

    ratio=1-(distancetogo/lenght);

    POINT p;
    p.x= line.start.x + ((line.end.x-line.start.x)*ratio);
    p.y= line.start.y + ((line.end.y-line.start.y)*ratio);
    p.z= line.start.z + ((line.end.z-line.start.z)*ratio);

    if(debug){
        std::cout<<"blocklenght:"<<lenght<<std::endl;
        std::cout<<"ratio:"<<ratio<<std::endl;
        std::cout<<"posx:"<<p.x<<" y:"<<p.y<<" z:"<<p.z<<std::endl;
        std::cout<<""<<std::endl;
    }
    return p;
}

POINT interpolate_arc(BLOCK arc, double distancetogo, bool debug){

    double radius=sqrt(pow(arc.end.x-arc.center.x,2)+pow(arc.end.y-arc.center.y,2)+pow(arc.end.z-arc.center.z,2));
    double diameter=radius*2;
    double circumfence=diameter*M_PI;
    double start_angle, end_angle, arc_angle, arc_lenght;

    if(arc.blocktype==BLOCKTYPE::G2){
        start_angle = atan2(arc.end.y-arc.center.y, arc.end.x-arc.center.x);
        end_angle = atan2(arc.start.y-arc.center.y, arc.start.x-arc.center.x);
    }

    if(arc.blocktype==BLOCKTYPE::G3){
        start_angle = atan2(arc.start.y-arc.center.y, arc.start.x-arc.center.x);
        end_angle = atan2(arc.end.y-arc.center.y, arc.end.x-arc.center.x);
    }

    if(end_angle < start_angle){  //this to avoid the start angle is bigger then the end angle value
        end_angle += 2*M_PI;
    }

    arc_angle=end_angle-start_angle;
    arc_lenght=(arc_angle/(2*M_PI))*circumfence;

    double ratio=distancetogo/arc_lenght;
    double angle_of_ratio=0;
    if(arc.blocktype==BLOCKTYPE::G2){
        angle_of_ratio=ratio*arc_angle;
    }
    if(arc.blocktype==BLOCKTYPE::G3){
        angle_of_ratio=(1-ratio)*arc_angle;
    }

    double rotated_x = cos(angle_of_ratio)* radius - sin(angle_of_ratio) * 0;
    double rotated_y = sin(angle_of_ratio)* radius + cos(angle_of_ratio) * 0;
    POINT p;
    p.x = rotated_x + arc.center.x;
    p.y = rotated_y + arc.center.y;
    p.z = arc.center.z;

    if(debug){
        if(arc.blocktype==BLOCKTYPE::G2){
            std::cout<<"arc of type G2"<<std::endl;
        }
        if(arc.blocktype==BLOCKTYPE::G3){
            std::cout<<"arc of type G3"<<std::endl;
        }
        std::cout<<"diameter:"<<diameter<<std::endl;
        std::cout<<"circumfence:"<<circumfence<<std::endl;
        std::cout<<"start_angle:"<<start_angle<<std::endl;
        std::cout<<"end_angle:"<<end_angle<<std::endl;
        std::cout<<"arclenght:"<<arc_lenght<<std::endl;
        std::cout<<"ratio:"<<ratio<<std::endl;
        std::cout<<"tcp_x:"<<p.x<<" y:"<<p.y<<" z:"<<p.z<<std::endl;
        std::cout<<""<<std::endl;
    }
    return p;
}
