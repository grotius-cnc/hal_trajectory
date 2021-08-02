#ifndef CPP_INTERFACE_H
#define CPP_INTERFACE_H

#include "cpp_interface_global.h"
#include <iostream>
#include <vector>
#include <fstream>

//! https://github.com/pantor/ruckig
//! A online-offline trajectory planner.
#include <ruckig.hpp>

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

struct TCP {
    POINT p;
    double vel,acc,jerk,pos;
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
