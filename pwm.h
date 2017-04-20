/*
 * pwm.h
 *
 *  Created on: Apr 17, 2017
 *      Author: yxa8247
 */

#define IO_PORT_SIZE            1		/* Define port size to 1 */
#define PA_ADDRESS              0x288	/* Digital I/O Port A: Register Address */
#define PB_ADDRESS              0x289	/* Digital I/O Port B: Register Address */
#define CTRL_ADDRESS            0x28B	/* Digital I/O Direction Control Register Address */
#define LOW                     0x00;
#define HIGH                    0x01;
#define CONTROL_REGISTER_CONFIG 0x00

void check_permission(void);
void pwm_init(void);

void* pwm_pa(void*);
void* pwm_pb(void*);

