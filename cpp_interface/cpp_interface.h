#ifndef CPP_INTERFACE_H
#define CPP_INTERFACE_H

#include "cpp_interface_global.h"
#include <iostream>
#include <vector>
#include <fstream>

//! https://github.com/pantor/ruckig
//! A online-offline trajectory planner.
#include "libruckig/ruckig.hpp"

//! Filedialog library.
#include <libdialog/portable-file-dialogs.h>
#if _WIN32
#define DEFAULT_PATH "C:\\"
#else
#define DEFAULT_PATH "/tmp"
#endif

//! Gcode reader library.
#include <libgcoderead/parser.h>

#include <libskynet/directory.h>

//! A struct that represent a 3d point.
struct POINT {
    double x,y,z;
};

//! A struct that represents a direction vector.
struct EULER{
    double euler_x, euler_y, euler_z;
};

struct TCP {
    POINT p;
    EULER e;
    double vel,acc,jerk,pos;
    bool m3,m7,m8;
    double power_rpm;
};


class CPP_INTERFACE_EXPORT Cpp_interface
{
public:
    Cpp_interface();

    void load_gcode(char* name);
    TCP trajectory_auto(double velocity_override,
                        bool start, bool stop, bool pause, bool resume,
                        double vel, double acc, double jerk,
                        unsigned int startfromblock, double tcp_x, double tcp_y, double tcp_z);
    TCP trajectory_jog(int jog_x, int jog_y, int jog_z,
                       int jog_euler_x, int jog_euler_y, int jog_euler_z,
                       double vel, double acc, double jerk,
                       double tcp_x, double tcp_y, double tcp_z,
                       double tcp_euler_x, double tcp_euler_y, double tcp_euler_z);
};

#endif // CPP_INTERFACE_H
