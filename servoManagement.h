#include <stdint.h>			/* for uintptr_t */

#define MOV (0x20)
#define WAIT (0x40)
#define LOOP (0x80)
#define END_LOOP (0xA0)
#define RECIPE_END (0x00)
#define JUMP (0xE0)
#define PEND (0xC0)

//typedef enum Channel Channel
enum Channel {
	CHANNEL_1_id, CHANNEL_2_id
};

typedef struct Servo Servo;
struct Servo
{
		uint8_t recipe[50];
		int wait;
		int recipe_id;
		int loop_id;
		int s_loop_id;
		int present_location;
		int recipe_finished;
		enum Channel channel;
		int pause;
		int pending;
		int signal;
};

extern Servo servo0, servo1;

void servo_cmd(char* cmd, Servo* servo0, Servo* servo1);
void operate(Servo* e);
void servo_init(Servo* e, enum Channel channel_id);
void servo_move(Servo* e, uint8_t val);
void servo_wait(Servo* e, uint8_t val);
void servo_loop(Servo* e, uint8_t val);
void servo_end_loop(Servo* e);
void Recipe_End(Servo* e);
void Jump(Servo* e, uint8_t val);
void Pend(Servo* e);
int left(Servo* e);
int right(Servo* e);
void Restart(Servo* e);
