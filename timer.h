/*
 * timer.h
 *
 *  Created on: Apr 3, 2017
 *      Author: yxa8247
 */

// used for timer pulse
#define MY_PULSE   	_PULSE_CODE_MINAVAIL
#define HMS   		100000000;      // 10^8 nano second = 100ms

/* declare global variable that timer.c and banking_project.c shares */
extern int system_time;

void* general_time(void*);

