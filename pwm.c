#include <stdint.h>			/* for uintptr_t */
#include <pthread.h>		/* for running thread */
#include <unistd.h>			/* for sleep */
#include <sys/neutrino.h>	/* for ThreadCtl() in QNX */
#include <sys/mman.h>		/* for mmap_device_io() */
#include <hw/inout.h>     	/* for in*() and out*() functions */
#include "pwm.h"

int pwm_init(void) {
	uintptr_t ctrl_handle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);		/* Get a handle to the Control register */
	uintptr_t pa_handle = mmap_device_io(IO_PORT_SIZE, PA_ADDRESS);			/* Get a handle to the Port A register */
	uintptr_t pb_handle = mmap_device_io(IO_PORT_SIZE, PB_ADDRESS);			/* Get a handle to the Port B register */

    if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1) {
        perror("Failed to get I/O access permission");
        return 1;
    }
    /* get GPIO Port A register */
    if(ctrl_handle == MAP_DEVICE_FAILED) {
        perror("Failed to map control register");
        return 2;
    }
    /* get handler for data register */
    if(pa_handle == MAP_DEVICE_FAILED) {
        perror("Failed to map Port A register");
        return 2;
    }
    /* get handler for data register */
    if(pb_handle == MAP_DEVICE_FAILED) {
        perror("Failed to map Port B register");
        return 2;
    }

    out8(ctrl_handle, CONTROL_REGISTER_CONFIG);      // set PORTs into output mode
    return 0;

}

void* pwm_pa(void* arg) {
	uintptr_t pa_handle = mmap_device_io(IO_PORT_SIZE, PA_ADDRESS);			/* Get a handle to the Port A register */
	struct timespec pwm_sleep, end_time;
	int time;
	int pos = 0;

	while (1) {
		switch (pos) {
			case 0:
				time = P0;
				break;
			case 1:
				time = P1;
				break;
			case 2:
				time = P2;
				break;
			case 3:
				time = P3;
				break;
			case 4:
				time = P4;
				break;
			case 5:
				time = P5;
				break;
		}
		out8( pa_handle, (uint8_t)0x01 );	// set high
		pwm_sleep.tv_nsec = time;
		nanosleep(&pwm_sleep, &end_time);

		out8( pa_handle, (uint8_t)0x00);	// set low
		pwm_sleep.tv_nsec = PERIOD - time;
		nanosleep(&pwm_sleep, &end_time);
	}
	return 0;
}

void* pwm_pb(void* arg) {
	uintptr_t pb_handle = mmap_device_io(IO_PORT_SIZE, PB_ADDRESS);			/* Get a handle to the Port A register */
	struct timespec pwm_sleep, end_time;
	int time;
	int pos = 5;

	while (1) {
		switch (pos) {
			case 0:
				time = P0;
				break;
			case 1:
				time = P1;
				break;
			case 2:
				time = P2;
				break;
			case 3:
				time = P3;
				break;
			case 4:
				time = P4;
				break;
			case 5:
				time = P5;
				break;
		}
		out8( pb_handle, (uint8_t)0x01 );	// set high
		pwm_sleep.tv_nsec = time;
		nanosleep(&pwm_sleep, &end_time);

		out8( pb_handle, (uint8_t)0x00);	// set low
		pwm_sleep.tv_nsec = PERIOD - time;
		nanosleep(&pwm_sleep, &end_time);
	}
	return 0;
}

