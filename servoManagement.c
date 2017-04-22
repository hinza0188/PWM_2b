/*
 * engineManagement.c
 *
 */

#include "servoManagement.h"

/*
 Function in charge of calling the right function after the user pressed enter with a new command
 */
void servo_cmd(char cmd[], Servo* servo0, Servo* servo1) {
	switch (cmd[0]) {
		case 'c':
		case 'C':
			servo0->pause = 0;
			break;
		case 'p':
		case 'P':
			servo0->pause = 1;
			break;
		case 'l':
		case 'L':
			left(servo0);
			break;
		case 'r':
		case 'R':
			right(servo0);
			break;
		case 'b':
		case 'B':
			Restart(servo0);
			break;
		case 'n':
		case 'N':
			break;
		case 'j':
		case 'J':
			Jump(servo0);
		case 'p':
		case 'P':
			Pend(servo0);
		default:
			break;
	}

	switch (cmd[1]) {
		case 'c':
		case 'C':
			servo1->pause = 0;
			break;
		case 'p':
		case 'P':
			servo1->pause = 1;
			break;
		case 'l':
		case 'L':
			left(servo1);
			break;
		case 'r':
		case 'R':
			right(servo1);
			break;
		case 'b':
		case 'B':
			Restart(servo1);
			break;
		case 'n':
		case 'N':
			break;
		case 'j':
		case 'J':
			Jump(servo1);
		case 'p':
		case 'P':
			Pend(servo1);
		default:
			break;
	}
}

/*
	Initialisation of an Engine struct
*/
void servo_init(Servo* e, enum Channel channel_index) {
	e->loop_id = 0;
	e->recipe_id = 0;
	e->s_loop_id = 0;
	e->wait = 10;
	e->present_location = 0;
	e->recipe_finished = 0;
	e->channel = channel_index;
	e->pause = 0 ;
	e->pending = 0;
	e->signal = 0;
}

/*
	Function called in the interrupt handler and in charge of following the recipe
	Calls the right function with the right parameters from a recipe instruction
*/
void operate (Servo* e) {

	if(!e->recipe_finished && !e->pause&& !e->pending)
        {
		if(e->wait != 0)
        {
			e->wait--;
        }
		else {
			switch(e->recipe[e->recipe_id] & 0xE0) {
				case MOV	:
					servo_move(e, e->recipe[e->recipe_id] & 0x1F);
					break;

				case WAIT  :
					servo_wait(e, e->recipe[e->recipe_id] & 0x1F);
					break;

				 case LOOP  :
					servo_loop(e, e->recipe[e->recipe_id] & 0x1F);
					break;

				 case END_LOOP  :
					servo_end_loop(e);
					break;

				 case RECIPE_END  :
					Recipe_End(e);
					break;

				 case JUMP :
					Jump(e, e->recipe[e->recipe_id] & 0x1F);
					break;

				 case PEND :
					 Pend(e);
					 break;

			}
			e->recipe_id++;
		}
	}
}

/*
	Recipe function which move the engine to a given position
*/
void servo_move(Servo* e, uint8_t val) {
	e->signal = (int)val;
	if(val > e->present_location) {
		e->wait = 2 * (val - e->present_location);
	}
	else {
		e->wait = -2 * (val - e->present_location);
	}

	e->present_location = val;
}


/*
	Recipe function making an engine wait for a given amount of time
*/
void servo_wait(Servo* e, uint8_t val) {
	e->wait = val;
}

/*
	Recipe function managing the loop
*/
void servo_loop(Servo* e, uint8_t val) {
	e->s_loop_id = e->recipe_id;
	e->loop_id = val;
}

/*
	Recipe function going back on the start of the loop if the loop_index isn't equal to 0
*/
void servo_end_loop(Servo* e) {
	if(e->loop_id != 0) {
		e->recipe_id = e->s_loop_id;
		e->loop_id--;
	}
}

/*
	End of the Recipe
*/
void Recipe_End(Servo* e) {
	e->recipe_finished = 1;
}

/*
	ADDITIONAL FUNCTION
	Recipe function jumping on the given instruction of the recipe
*/
void Jump(Servo* e, uint8_t val) {
	e->recipe_id = val-1;
}

/*
	ADDITIONAL FUNCTION
	Recipe function waiting for both engines to be on pending to start again
	Could be use as a synchronize function
*/
void Pend(Servo* e) {
	e->pending = 1;
}

/*
	Make the enginne go left if possible
*/
int left(Servo* e) {
	if(e->present_location != 5 && (e->pause || e->recipe_finished)) {
		e->signal++;
		e->present_location++;
		return 0;
	}
	else return -1;
}

/*
	Make the enginne go right if possible
*/
int right(Servo* e) {
	if(e->present_location != 0 && (e->pause || e->recipe_finished)) {
		e->signal--;
		e->present_location--;
		return 0;
	}
	else return -1;
}

/*
	Restart the recipe of an engine
*/
void Restart(Servo* e) {
	e->signal = 0;
	e->present_location = 0;
	e->loop_id = 0;
	e->recipe_id = 0;
	e->recipe_finished = 0;
	e->s_loop_id = 0;
	e->wait = 10;
}
