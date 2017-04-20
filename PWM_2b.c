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


// declare variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char *argv[]) {
    pwm_init();
    
    pthread_create( NULL, NULL, &general_time, NULL);       // increment timer tick by every 1 ns
    pthread_create( NULL, NULL, pwm_pa, NULL);
    pthread_create( NULL, NULL, pwm_pb, NULL);

	sleep(60);

	return EXIT_SUCCESS;
}
