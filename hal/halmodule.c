#include "rtapi.h"
#include "rtapi_ctype.h"
#include "rtapi_app.h"
#include "rtapi_string.h"
#include "rtapi_errno.h"
#include "rtapi_math64.h"
#include <rtapi_io.h>
#include "hal.h"
#include <halmodule.h>

/* module information */
MODULE_AUTHOR("Skynet");
MODULE_DESCRIPTION("Halmodule trajectory");
MODULE_LICENSE("GPL");

static int comp_idx;

typedef struct {
    bool ok;
} skynet_t;
skynet_t *skynet;

typedef struct {
    hal_float_t *Pin;
} float_data_t;
//! Input pins:
float_data_t *max_velocity;
float_data_t *max_acceleration;
float_data_t *max_jerk;
float_data_t *current_position;
float_data_t *current_velocity;
float_data_t *current_acceleration;

//! Output pins:
float_data_t *tcp_x, *tcp_y, *tcp_z;

//! Pins
typedef struct {
    hal_bit_t *Pin;
} bit_data_t;
bit_data_t *enable;

typedef struct {
    hal_s32_t *Pin;
} s32_data_t;

typedef struct {
    hal_u32_t *Pin;
} u32_data_t;

typedef struct {
    hal_port_t *Pin;
} port_data_t;

//! Params
typedef struct {
    hal_float_t Pin;
} param_float_data_t;

typedef struct {
    hal_bit_t Pin;
} param_bit_data_t;
param_bit_data_t *dummy;

static int comp_idx; /* component ID */
struct TCP tcp;

static void trajectory();
static int setup_pins();

int rtapi_app_main(void) {

    int r = 0;
    comp_idx = hal_init("trajectory");
    if(comp_idx < 0) return comp_idx;
    r = hal_export_funct("trajectory", trajectory, &skynet,0,0,comp_idx);

    r+=setup_pins();
    // Set dummy values.
    *max_velocity->Pin=5000;
    *max_acceleration->Pin=3000;
    *max_jerk->Pin=500;
    // *enable->Pin=1;

    // Load a sample gcode.
    wrapper_load_gcode();

    if(r) {
        hal_exit(comp_idx);
    } else {
        hal_ready(comp_idx);
    }
    return 0;
}

void rtapi_app_exit(void){
    hal_exit(comp_idx);
}

//! Perforn's every ms.
static void trajectory(){

    if(*enable->Pin==1){
        // Velocity +/- will move the machine.
        unsigned int startfromblock=0;
        double tcpx=0;
        double tcpy=0;
        double tcpz=0;

        // Robot offsets
        // Kuka x=630, y=0, z=890
        double x=630, y=0, z=500;

        tcp=wrapper_trajectory(*max_velocity->Pin,*max_acceleration->Pin,*max_jerk->Pin, startfromblock, tcpx, tcpy, tcpz);
        *tcp_x->Pin=tcp.p.x+x;
        *tcp_y->Pin=tcp.p.y+y;
        *tcp_z->Pin=tcp.p.z+z;
        *current_velocity->Pin=tcp.vel;
        *current_acceleration->Pin=tcp.acc;
        *current_position->Pin=tcp.pos;
    }
}

static int setup_pins(){
    int r=0;

    //! Input pins, type bit.
    enable = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("enable",HAL_IN,&(enable->Pin),comp_idx);

    //! Input pins, type float.
    max_velocity = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_velocity",HAL_IN,&(max_velocity->Pin),comp_idx);

    max_acceleration = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_acceleration",HAL_IN,&(max_acceleration->Pin),comp_idx);

    max_jerk = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_jerk",HAL_IN,&(max_jerk->Pin),comp_idx);


    //! Output pins, type float.
    tcp_x = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("tcp_x",HAL_OUT,&(tcp_x->Pin),comp_idx);

    tcp_y = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("tcp_y",HAL_OUT,&(tcp_y->Pin),comp_idx);

    tcp_z = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("tcp_z",HAL_OUT,&(tcp_z->Pin),comp_idx);


    current_position = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_position",HAL_OUT,&(current_position->Pin),comp_idx);

    current_velocity = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_velocity",HAL_OUT,&(current_velocity->Pin),comp_idx);

    current_acceleration = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_acceleration",HAL_OUT,&(current_acceleration->Pin),comp_idx);

    return r;
}







































