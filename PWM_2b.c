#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>			/* for uintptr_t */
#include <pthread.h>		/* for running thread */
#include <time.h>			/* for general timer */
#include <unistd.h>			/* for sleep */
#include <sys/neutrino.h>	/* for ThreadCtl() in QNX */
#include <sys/mman.h>		/* for mmap_device_io() */
#include "recipe.h"
#include "pwm.h"
#include "timer.h"

// define values
#define MAX_CMD_VALUE 2;

// declare variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
uint8_t buff[100];
Servo servo0, servo1;


int main(int argc, char *argv[]) {
	/* Declare variables */
	char str[2];

	struct _clockperiod clkper;
	clkper.nsec = 10000;
	clkper.fract = 0;
	ClockPeriod(CLOCK_REALTIME, &clkper, NULL, 0);

    /* Initialize threads */
	PWM_Init();
	/* Initialize Servo 0 with recipe 2 @ position_0 */
    servo_init(&servo0, CHANNEL_1_id);
    Recipe1(&servo0);
    /* Initialize Servo 1 with recipe 2 @ position_0 */
    servo_init(&servo0, CHANNEL_2_id);
    Recipe2(&servo1);
    
    printf("New Test...\n");

    pthread_create( NULL, NULL, &general_time, NULL);       // increment timer tick by every 1 ns
	pthread_create( NULL, NULL, pwm_pa, (void*)&servo0);
	pthread_create( NULL, NULL, pwm_pb, (void*)&servo1);

	while(1) {
		printf("Enter the command: ");
		scanf("%s", str);
		// use str to run recipe command here
		printf("Input Taken: %s\n", str);
		servo_cmd(str, &servo0, &servo1);
	}

	return EXIT_SUCCESS;
}
