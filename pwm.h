/*
 * pwm.h
 *
 *  Created on: Apr 17, 2017
 *      Author: yxa8247
 */

#ifndef __PWM__
#define __PWM__

#define IO_PORT_SIZE            1			/* Define port size to 1 */
#define PA_ADDRESS              0x288		/* Digital I/O Port A: Register Address */
#define PB_ADDRESS              0x289		/* Digital I/O Port B: Register Address */
#define CTRL_ADDRESS            0x28B		/* Digital I/O Direction Control Register Address */
#define CONTROL_REGISTER_CONFIG 0x00
#define PERIOD   				20000000;   /* 2 * 10^7 nano second = 20ms */
#define P0 (388000)
#define P1 (720000)
#define P2 (1100000)
#define P3 (1450000)
#define P4 (1850000)
#define P5 (2140000)

void check_permission(void);
int PWM_Init(void);

void* pwm_pa(void*);
void* pwm_pb(void*);

#endif //__PWM__

