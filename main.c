#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>			/* for uintptr_t */
#include <pthread.h>		/* for running thread */
#include <time.h>			/* for general timer */
#include <unistd.h>			/* for sleep */
#include <sys/neutrino.h>	/* for ThreadCtl() in QNX */
#include <sys/mman.h>		/* for mmap_device_io() */
#include "pwm.h"
#include "timer.h"

#define IO_PORT_SIZE 1		/* Define port size to 1 */
#define PA_ADDRESS 0x288	/* Digital I/O Port A: Register Address */
#define PB_ADDRESS 0x289	/* Digital I/O Port B: Register Address */
#define CTRL_ADDRESS 0x28B	/* Digital I/O Direction Control Register Address */

// declare variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int system_time = 0;

void* func1( void* arg) {
	return 1;
}

void check_permission() {
	uintptr_t ctrl_handle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);		/* Get a handle to the Control register */
	uintptr_t pa_handle = mmap_device_io(IO_PORT_SIZE, PA_ADDRESS);			/* Get a handle to the Port A register */
	uintptr_t pb_handle = mmap_device_io(IO_PORT_SIZE, PB_ADDRESS);			/* Get a handle to the Port B register */

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
}

int main(int argc, char *argv[]) {
	check_permission();

    pthread_create( NULL, NULL, &general_time, NULL);       // increment timer tick by every 1 ns
	pthread_create( NULL, NULL, &func1, NULL);
	sleep(10);

	return EXIT_SUCCESS;
}
