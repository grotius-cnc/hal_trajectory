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

typedef struct {
    hal_bit_t *Pin;
} bit_data_t;
bit_data_t *bit0, *bit1, *bit2, *bit3, *bit4;

typedef struct {
    hal_float_t Pin;
} param_data_t;

typedef struct {
    hal_s32_t *Pin;
} s32_data_t;

typedef struct {
    hal_u32_t *Pin;
} u32_data_t;

typedef struct {
    hal_port_t *Pin;
} port_data_t;
port_data_t *P1,*P2;

static int comp_idx;		/* component ID */

static void read();
static void write();

int trigger=0;

int rtapi_app_main(void) {

    int r = 0;
    comp_idx = hal_init("trajectory");
    if(comp_idx < 0) return comp_idx;
    r = hal_export_funct("read", read, &skynet,0,0,comp_idx);
    r = hal_export_funct("write", write, &skynet,0,0,comp_idx);

    bit0 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("bit0",HAL_IN,&(bit0->Pin),comp_idx);

    bit1 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("bit1",HAL_IN,&(bit1->Pin),comp_idx);

    bit2 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("bit2",HAL_OUT,&(bit2->Pin),comp_idx);

    bit3 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("train",HAL_IN,&(bit3->Pin),comp_idx);

    bit4 = (bit_data_t*)hal_malloc(sizeof(bit_data_t));
    r+=hal_pin_bit_new("run",HAL_IN,&(bit4->Pin),comp_idx);

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
    if(trigger==0){
    struct data d;
    for(unsigned int i=0; i<6; i++){

        d.max_velocity[i]=1.2;
        d.max_acceleration[i]=4.0;
        d.max_jerk[i]=10.0;
        d.current_position[i]=0.0;
        d.current_velocity[i]=0.0;
        d.current_acceleration[i]=0.0;
        d.target_position[i]=5.0;
        d.target_velocity[i]=0.0;
        d.target_acceleration[i]=0.0;
    }

    function(d);
    trigger=1;
    }
}

static void write()
{

}










