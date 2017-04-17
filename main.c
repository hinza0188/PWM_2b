#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>			/* for uintptr_t */
#include <pthread.h>		/* for running thread */
#include <time.h>			/* for general timer */
#include <unistd.h>			/* for sleep */
#include <sys/neutrino.h>	/* for ThreadCtl() */
#include <sys/mman.h>		/* for mmap_device_io() */
#include "pwm.h"

#define IO_PORT_SIZE 1		/* Define port size to 1 */
#define PA_ADDRESS 0x288	/* Digital I/O Port A: Register Address */
#define CTRL_ADDRESS 0x28B	/* Digital I/O Direction Control Register Address */

// declare variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* func1( void* arg) {
	return 1;
}

int main(int argc, char *argv[]) {
	/* declare variables */
	int permission_err =  ThreadCtl( _NTO_TCTL_IO, NULL );	/* give this thread root permission */
	uintptr_t ctrl_handle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);		/* Get a handle to the Control register */
	uintptr_t data_handle = mmap_device_io(IO_PORT_SIZE, DATA_ADDRESS);		/* Get a handle to the Data register */

	/* get thread permission 1 */
	if ( permission_err == -1) {
		perror("Failed to get I/O access permission");
		return 1;
	}
	/* get handler for control register */
	if(ctrlHandle == MAP_DEVICE_FAILED) {
		perror("Failed to map control register");
		return 2;
	}
	/* get handler for data register */
	if(PA == MAP_DEVICE_FAILED) {
		perror("Failed to map Port register");
		return 2;
	}

	pthread_create( NULL, NULL, &func1, NULL);
	sleep(10);

	return EXIT_SUCCESS;
}
