/*
 * pwm.h
 *
 *  Created on: Apr 17, 2017
 *      Author: yxa8247
 */

#define IO_PORT_SIZE            1			/* Define port size to 1 */
#define PA_ADDRESS              0x288		/* Digital I/O Port A: Register Address */
#define PB_ADDRESS              0x289		/* Digital I/O Port B: Register Address */
#define CTRL_ADDRESS            0x28B		/* Digital I/O Direction Control Register Address */
#define CONTROL_REGISTER_CONFIG 0x00
#define PERIOD   				20000000;   /* 2 * 10^7 nano second = 20ms */
#define P0						388000;		/* position 0, 0.388ms of servo duty */
#define P1						750000;
#define P2						1100000;
#define P3						1450000;
#define P4						1850000;
#define P5						2140000;	/* position 5, 2.140ms of servo duty */


void check_permission(void);
int pwm_init(void);

void* pwm_pa(void*);
void* pwm_pb(void*);

