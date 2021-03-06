/*
 * timer.c
 *
 *  Created on: Apr 3, 2017
 *      Author: yxa8247
 */
#include <stdio.h>
#include <time.h>
#include <sys/netmgr.h>
#include <sys/neutrino.h>
#include <sys/mman.h>		/* for mmap_device_io() */
#include "timer.h"
#include "pwm.h"
#include "servoManagement.h"


/* handling pulse as timer's message */
typedef union {
        struct _pulse   pulse;
} my_message_t;


/**
 * Runs QNX timer for general time counting purposes 
 */
void* general_time(void* arg) {
	struct sigevent event;
	struct itimerspec itime;
	timer_t timer_id;
	int chid, rcvid;
	my_message_t msg;

    chid = ChannelCreate(0);

    event.sigev_notify = SIGEV_PULSE;
    event.sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0, chid, _NTO_SIDE_CHANNEL, 0);
    event.sigev_priority = getprio(0);
    event.sigev_code = MY_PULSE;
    timer_create(CLOCK_REALTIME, &event, &timer_id);

    /* set timer to be interuupted every second */
    itime.it_value.tv_nsec = HMS;
    /* set timer to be interuupted every second */
    itime.it_interval.tv_nsec = HMS;
    timer_settime(timer_id, 0, &itime, NULL);

    for (;;) {
        rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
        if (rcvid == 0) { /* pulse detected from the timer */
            if (msg.pulse.code == MY_PULSE) {
                // 100 MS has been ticked!
            	operate(&servo0);
				operate(&servo1);
            }
       }
    }
    return 0;
}
