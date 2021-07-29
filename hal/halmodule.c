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

/* Usage example :
 *
 * halcmd stop
 * halcmd loadrt threads name1=base-thread fp1=0 period1=25000 name2=servo-thread period2=1000000
 * halcmd loadrt trajectory
 * halcmd init
 * halcmd addf read servo-thread
 * halcmd addf write servo-thread
 * halcmd start
 *
 */

static int comp_idx;

typedef struct {
    bool ok;
} skynet_t;
skynet_t *skynet;

typedef struct {
    hal_float_t *Pin;
} float_data_t;
//! Input pins:
float_data_t *max_velocity_0, *max_velocity_1, *max_velocity_2, *max_velocity_3, *max_velocity_4, *max_velocity_5;
float_data_t *max_acceleration_0, *max_acceleration_1, *max_acceleration_2, *max_acceleration_3, *max_acceleration_4, *max_acceleration_5;
float_data_t *max_jerk_0, *max_jerk_1, *max_jerk_2, *max_jerk_3, *max_jerk_4, *max_jerk_5;
float_data_t *current_position_0, *current_position_1, *current_position_2, *current_position_3, *current_position_4, *current_position_5;
float_data_t *current_velocity_0, *current_velocity_1, *current_velocity_2, *current_velocity_3, *current_velocity_4, *current_velocity_5;
float_data_t *current_acceleration_0, *current_acceleration_1, *current_acceleration_2, *current_acceleration_3, *current_acceleration_4, *current_acceleration_5;
float_data_t *target_position_0, *target_position_1, *target_position_2, *target_position_3, *target_position_4, *target_position_5;
float_data_t *target_velocity_0, *target_velocity_1, *target_velocity_2, *target_velocity_3, *target_velocity_4, *target_velocity_5;
float_data_t *target_acceleration_0, *target_acceleration_1, *target_acceleration_2, *target_acceleration_3, *target_acceleration_4, *target_acceleration_5;

//! Output pins:
float_data_t *position_0, *position_1, *position_2, *position_3, *position_4, *position_5;
float_data_t *velocity_0, *velocity_1, *velocity_2, *velocity_3, *velocity_4, *velocity_5;
float_data_t *acceleration_0, *acceleration_1, *acceleration_2, *acceleration_3, *acceleration_4, *acceleration_5;

//! Pins
typedef struct {
    hal_bit_t *Pin;
} bit_data_t;
bit_data_t *trajectory_ready;

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
param_bit_data_t *trajectory_request;

static int comp_idx; /* component ID */

static void read();
static void write();
static void example();
static int setup_pins();
static struct data get_trajectory_parameters();

int trigger=0;
bool busy=0;
double trajectory_time=0;
double sec=0;

int rtapi_app_main(void) {

    int r = 0;
    comp_idx = hal_init("trajectory");
    if(comp_idx < 0) return comp_idx;
    r = hal_export_funct("read", read, &skynet,0,0,comp_idx);
    r = hal_export_funct("write", write, &skynet,0,0,comp_idx);

    r+=setup_pins();

    //! Initialize as true;
    *trajectory_ready->Pin=true;

    //! Testsuite, startup in endless loop:
    // trajectory_request->Pin=true;

    if(r) {
        hal_exit(comp_idx);
    } else {
        hal_ready(comp_idx);
    }
    return 0;
}

void rtapi_app_exit(void) {
    hal_exit(comp_idx);
}

static void read()
{
    if(trajectory_request->Pin && !busy){
        struct data d=get_trajectory_parameters();
        wrapper_trajectory_init(d);
        trajectory_time=wrapper_trajectory_time();
        rtapi_print_msg(RTAPI_MSG_ERR,"trajectory_time: %f \n", trajectory_time);

        //! The request is done.
        busy=true;
        sec=0;
        *trajectory_ready->Pin=false;
        //! Disable for endless loop:
        // trajectory_request->Pin=false;
    }
}

static void write()
{  
    if(busy){
        //! Increase ms every servo-thread call.
        sec+=0.001;
        rtapi_print_msg(RTAPI_MSG_ERR,"seconds: %f \n", sec);
        //! Perform trajectory until time is finished.
        if(sec<=trajectory_time){
            struct pos p=wrapper_trajectory_at_time(sec);

            *position_0->Pin=p.position[0];
            *position_1->Pin=p.position[1];
            *position_2->Pin=p.position[2];
            *position_3->Pin=p.position[3];
            *position_4->Pin=p.position[4];
            *position_5->Pin=p.position[5];

            *velocity_0->Pin=p.velocity[0];
            *velocity_1->Pin=p.velocity[1];
            *velocity_2->Pin=p.velocity[2];
            *velocity_3->Pin=p.velocity[3];
            *velocity_4->Pin=p.velocity[4];
            *velocity_5->Pin=p.velocity[5];

            *acceleration_0->Pin=p.acceleration[0];
            *acceleration_1->Pin=p.acceleration[1];
            *acceleration_2->Pin=p.acceleration[2];
            *acceleration_3->Pin=p.acceleration[3];
            *acceleration_4->Pin=p.acceleration[4];
            *acceleration_5->Pin=p.acceleration[5];
        } else {
            busy=false;
            *trajectory_ready->Pin=true;
        }
    }
}

//! Different example's how to use the trajectory library.
static void example()
{
    if(trigger==0){
        struct data d;
        for(unsigned int i=0; i<6; i++){

            d.max_velocity[i]=1.2;
            d.max_acceleration[i]=4.0;
            d.max_jerk[i]=10.0;
            d.current_position[i]=0.0;
            d.current_velocity[i]=0.0;
            d.current_acceleration[i]=0.0;
            d.target_position[i]=2.0;
            d.target_velocity[i]=0.0;
            d.target_acceleration[i]=0.0;
        }

        wrapper_example(d);

        wrapper_trajectory_init(d);
        double time=wrapper_trajectory_time();
        rtapi_print_msg(RTAPI_MSG_ERR,"trajectory_time: %f \n", time);

        double at_time=2.0;
        struct pos p=wrapper_trajectory_at_time(at_time);
        rtapi_print_msg(RTAPI_MSG_ERR,"trajectory_at_time: %f \n", at_time);
        for(unsigned int i=0; i<6; i++){
            rtapi_print_msg(RTAPI_MSG_ERR,"position: %f \n", p.position[i]);
            rtapi_print_msg(RTAPI_MSG_ERR,"velocity: %f \n", p.velocity[i]);
            rtapi_print_msg(RTAPI_MSG_ERR,"acceleration: %f \n", p.acceleration[i]);
        }
        trigger=1;
    }
}

static int setup_pins(){
    int r=0;

    //! Input pins, type bit.
    trajectory_request = (param_bit_data_t*)hal_malloc(sizeof(param_bit_data_t));
    r+=hal_param_bit_new("trajectory_request",HAL_RW,&(trajectory_request->Pin),comp_idx);
    trajectory_ready = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("trajectory_ready",HAL_OUT,&(trajectory_ready->Pin),comp_idx);

    //! Input pins, type float.
    max_velocity_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_velocity_0",HAL_IN,&(max_velocity_0->Pin),comp_idx);
    max_velocity_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_velocity_1",HAL_IN,&(max_velocity_1->Pin),comp_idx);
    max_velocity_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_velocity_2",HAL_IN,&(max_velocity_2->Pin),comp_idx);
    max_velocity_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_velocity_3",HAL_IN,&(max_velocity_3->Pin),comp_idx);
    max_velocity_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_velocity_4",HAL_IN,&(max_velocity_4->Pin),comp_idx);
    max_velocity_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_velocity_5",HAL_IN,&(max_velocity_5->Pin),comp_idx);

    max_acceleration_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_acceleration_0",HAL_IN,&(max_acceleration_0->Pin),comp_idx);
    max_acceleration_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_acceleration_1",HAL_IN,&(max_acceleration_1->Pin),comp_idx);
    max_acceleration_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_acceleration_2",HAL_IN,&(max_acceleration_2->Pin),comp_idx);
    max_acceleration_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_acceleration_3",HAL_IN,&(max_acceleration_3->Pin),comp_idx);
    max_acceleration_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_acceleration_4",HAL_IN,&(max_acceleration_4->Pin),comp_idx);
    max_acceleration_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_acceleration_5",HAL_IN,&(max_acceleration_5->Pin),comp_idx);

    max_jerk_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_jerk_0",HAL_IN,&(max_jerk_0->Pin),comp_idx);
    max_jerk_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_jerk_1",HAL_IN,&(max_jerk_1->Pin),comp_idx);
    max_jerk_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_jerk_2",HAL_IN,&(max_jerk_2->Pin),comp_idx);
    max_jerk_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_jerk_3",HAL_IN,&(max_jerk_3->Pin),comp_idx);
    max_jerk_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_jerk_4",HAL_IN,&(max_jerk_4->Pin),comp_idx);
    max_jerk_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("max_jerk_5",HAL_IN,&(max_jerk_5->Pin),comp_idx);

    current_position_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_position_0",HAL_IN,&(current_position_0->Pin),comp_idx);
    current_position_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_position_1",HAL_IN,&(current_position_1->Pin),comp_idx);
    current_position_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_position_2",HAL_IN,&(current_position_2->Pin),comp_idx);
    current_position_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_position_3",HAL_IN,&(current_position_3->Pin),comp_idx);
    current_position_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_position_4",HAL_IN,&(current_position_4->Pin),comp_idx);
    current_position_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_position_5",HAL_IN,&(current_position_5->Pin),comp_idx);

    current_velocity_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_velocity_0",HAL_IN,&(current_velocity_0->Pin),comp_idx);
    current_velocity_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_velocity_1",HAL_IN,&(current_velocity_1->Pin),comp_idx);
    current_velocity_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_velocity_2",HAL_IN,&(current_velocity_2->Pin),comp_idx);
    current_velocity_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_velocity_3",HAL_IN,&(current_velocity_3->Pin),comp_idx);
    current_velocity_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_velocity_4",HAL_IN,&(current_velocity_4->Pin),comp_idx);
    current_velocity_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_velocity_5",HAL_IN,&(current_velocity_5->Pin),comp_idx);

    current_acceleration_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_acceleration_0",HAL_IN,&(current_acceleration_0->Pin),comp_idx);
    current_acceleration_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_acceleration_1",HAL_IN,&(current_acceleration_1->Pin),comp_idx);
    current_acceleration_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_acceleration_2",HAL_IN,&(current_acceleration_2->Pin),comp_idx);
    current_acceleration_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_acceleration_3",HAL_IN,&(current_acceleration_3->Pin),comp_idx);
    current_acceleration_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_acceleration_4",HAL_IN,&(current_acceleration_4->Pin),comp_idx);
    current_acceleration_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("current_acceleration_5",HAL_IN,&(current_acceleration_5->Pin),comp_idx);

    target_position_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_position_0",HAL_IN,&(target_position_0->Pin),comp_idx);
    target_position_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_position_1",HAL_IN,&(target_position_1->Pin),comp_idx);
    target_position_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_position_2",HAL_IN,&(target_position_2->Pin),comp_idx);
    target_position_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_position_3",HAL_IN,&(target_position_3->Pin),comp_idx);
    target_position_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_position_4",HAL_IN,&(target_position_4->Pin),comp_idx);
    target_position_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_position_5",HAL_IN,&(target_position_5->Pin),comp_idx);

    target_velocity_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_velocity_0",HAL_IN,&(target_velocity_0->Pin),comp_idx);
    target_velocity_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_velocity_1",HAL_IN,&(target_velocity_1->Pin),comp_idx);
    target_velocity_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_velocity_2",HAL_IN,&(target_velocity_2->Pin),comp_idx);
    target_velocity_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_velocity_3",HAL_IN,&(target_velocity_3->Pin),comp_idx);
    target_velocity_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_velocity_4",HAL_IN,&(target_velocity_4->Pin),comp_idx);
    target_velocity_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_velocity_5",HAL_IN,&(target_velocity_5->Pin),comp_idx);

    target_acceleration_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_acceleration_0",HAL_IN,&(target_acceleration_0->Pin),comp_idx);
    target_acceleration_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_acceleration_1",HAL_IN,&(target_acceleration_1->Pin),comp_idx);
    target_acceleration_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_acceleration_2",HAL_IN,&(target_acceleration_2->Pin),comp_idx);
    target_acceleration_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_acceleration_3",HAL_IN,&(target_acceleration_3->Pin),comp_idx);
    target_acceleration_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_acceleration_4",HAL_IN,&(target_acceleration_4->Pin),comp_idx);
    target_acceleration_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("target_acceleration_5",HAL_IN,&(target_acceleration_5->Pin),comp_idx);

    //! Output pins, type float.
    position_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("position_0",HAL_OUT,&(position_0->Pin),comp_idx);
    position_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("position_1",HAL_OUT,&(position_1->Pin),comp_idx);
    position_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("position_2",HAL_OUT,&(position_2->Pin),comp_idx);
    position_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("position_3",HAL_OUT,&(position_3->Pin),comp_idx);
    position_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("position_4",HAL_OUT,&(position_4->Pin),comp_idx);
    position_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("position_5",HAL_OUT,&(position_5->Pin),comp_idx);

    velocity_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("velocity_0",HAL_OUT,&(velocity_0->Pin),comp_idx);
    velocity_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("velocity_1",HAL_OUT,&(velocity_1->Pin),comp_idx);
    velocity_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("velocity_2",HAL_OUT,&(velocity_2->Pin),comp_idx);
    velocity_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("velocity_3",HAL_OUT,&(velocity_3->Pin),comp_idx);
    velocity_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("velocity_4",HAL_OUT,&(velocity_4->Pin),comp_idx);
    velocity_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("velocity_5",HAL_OUT,&(velocity_5->Pin),comp_idx);

    acceleration_0 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("acceleration_0",HAL_OUT,&(acceleration_0->Pin),comp_idx);
    acceleration_1 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("acceleration_1",HAL_OUT,&(acceleration_1->Pin),comp_idx);
    acceleration_2 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("acceleration_2",HAL_OUT,&(acceleration_2->Pin),comp_idx);
    acceleration_3 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("acceleration_3",HAL_OUT,&(acceleration_3->Pin),comp_idx);
    acceleration_4 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("acceleration_4",HAL_OUT,&(acceleration_4->Pin),comp_idx);
    acceleration_5 = (float_data_t*)hal_malloc(sizeof(float_data_t));
    r+=hal_pin_float_new("acceleration_5",HAL_OUT,&(acceleration_5->Pin),comp_idx);

    return r;
}

static struct data get_trajectory_parameters(){
    struct data d;
    int i=0;
    d.max_velocity[i]=*max_velocity_0->Pin;
    d.max_acceleration[i]=*max_acceleration_0->Pin;
    d.max_jerk[i]=*max_jerk_0->Pin;
    d.current_position[i]=*current_position_0->Pin;
    d.current_velocity[i]=*current_velocity_0->Pin;
    d.current_acceleration[i]=*current_acceleration_0->Pin;
    d.target_position[i]=*target_position_0->Pin;
    d.target_velocity[i]=*target_velocity_0->Pin;
    d.target_acceleration[i]=*target_acceleration_0->Pin;
    i++;
    d.max_velocity[i]=*max_velocity_1->Pin;
    d.max_acceleration[i]=*max_acceleration_1->Pin;
    d.max_jerk[i]=*max_jerk_1->Pin;
    d.current_position[i]=*current_position_1->Pin;
    d.current_velocity[i]=*current_velocity_1->Pin;
    d.current_acceleration[i]=*current_acceleration_1->Pin;
    d.target_position[i]=*target_position_1->Pin;
    d.target_velocity[i]=*target_velocity_1->Pin;
    d.target_acceleration[i]=*target_acceleration_1->Pin;
    i++;
    d.max_velocity[i]=*max_velocity_2->Pin;
    d.max_acceleration[i]=*max_acceleration_2->Pin;
    d.max_jerk[i]=*max_jerk_2->Pin;
    d.current_position[i]=*current_position_2->Pin;
    d.current_velocity[i]=*current_velocity_2->Pin;
    d.current_acceleration[i]=*current_acceleration_2->Pin;
    d.target_position[i]=*target_position_2->Pin;
    d.target_velocity[i]=*target_velocity_2->Pin;
    d.target_acceleration[i]=*target_acceleration_2->Pin;
    i++;
    d.max_velocity[i]=*max_velocity_3->Pin;
    d.max_acceleration[i]=*max_acceleration_3->Pin;
    d.max_jerk[i]=*max_jerk_3->Pin;
    d.current_position[i]=*current_position_3->Pin;
    d.current_velocity[i]=*current_velocity_3->Pin;
    d.current_acceleration[i]=*current_acceleration_3->Pin;
    d.target_position[i]=*target_position_3->Pin;
    d.target_velocity[i]=*target_velocity_3->Pin;
    d.target_acceleration[i]=*target_acceleration_3->Pin;
    i++;
    d.max_velocity[i]=*max_velocity_4->Pin;
    d.max_acceleration[i]=*max_acceleration_4->Pin;
    d.max_jerk[i]=*max_jerk_4->Pin;
    d.current_position[i]=*current_position_4->Pin;
    d.current_velocity[i]=*current_velocity_4->Pin;
    d.current_acceleration[i]=*current_acceleration_4->Pin;
    d.target_position[i]=*target_position_4->Pin;
    d.target_velocity[i]=*target_velocity_4->Pin;
    d.target_acceleration[i]=*target_acceleration_4->Pin;
    i++;
    d.max_velocity[i]=*max_velocity_5->Pin;
    d.max_acceleration[i]=*max_acceleration_5->Pin;
    d.max_jerk[i]=*max_jerk_5->Pin;
    d.current_position[i]=*current_position_5->Pin;
    d.current_velocity[i]=*current_velocity_5->Pin;
    d.current_acceleration[i]=*current_acceleration_5->Pin;
    d.target_position[i]=*target_position_5->Pin;
    d.target_velocity[i]=*target_velocity_5->Pin;
    d.target_acceleration[i]=*target_acceleration_5->Pin;

    return d;
}







