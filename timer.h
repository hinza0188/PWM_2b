/*
 * timer.h
 *
 *  Created on: Apr 3, 2017
 *      Author: yxa8247
 */

// used for timer pulse
#define MY_PULSE   _PULSE_CODE_MINAVAIL
#define 100MS   100000000;      // 10^8 nano second = 100ms
#define 20MS    20000000;      // 2*10^7 nano second = 20ms

/* declare global variable that timer.c and banking_project.c shares */
extern int system_time;
extern int period_tick;

void* general_time(void*);
void* pwm_period(void*);

