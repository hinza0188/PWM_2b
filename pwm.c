#include <stdint.h>			/* for uintptr_t */
#include <pthread.h>		/* for running thread */
#include <unistd.h>			/* for sleep */
#include <sys/neutrino.h>	/* for ThreadCtl() in QNX */
#include <sys/mman.h>		/* for mmap_device_io() */
#include "pwm.h"

uintptr_t ctrl_handle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);		/* Get a handle to the Control register */
uintptr_t pa_handle = mmap_device_io(IO_PORT_SIZE, PA_ADDRESS);			/* Get a handle to the Port A register */
uintptr_t pb_handle = mmap_device_io(IO_PORT_SIZE, PB_ADDRESS);			/* Get a handle to the Port B register */


void pwm_init(void) {
    if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1) {
        perror("Failed to get I/O access permission");
        return 1;
    }
    /* get GPIO Port A register */
    if(ctrlHandle == MAP_DEVICE_FAILED) {
        perror("Failed to map control register");
        return 2;
    }
    /* get handler for data register */
    if(pa_handle == MAP_DEVICE_FAILED) {
        perror("Failed to map Port register");
        return 2;
    }
    /* get handler for data register */
    if(pb_handle == MAP_DEVICE_FAILED) {
        perror("Failed to map Port register");
        return 2;
    }

    out8(ctrl_handle,CONTROL_REGISTER_CONFIG);      // set PORTs into output mode


}

void* pwm_pa(void* arg) {

	return 1;
}

void* pwm_pb(void* arg) {

	return 1;
}
