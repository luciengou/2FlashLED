#ifndef	__Loop_H__

#define __Loop_H__

typedef enum {
	SERVO_CHECK ,
	SERVO_HIGH_MID_LOW_CHECK ,
	SERVO_MOVE_STABLE ,
	MAIN_POWER_CHECK ,
	TOTAL_TIME_CHECK ,
} eWork_State;

static eWork_State Work_State_G = SERVO_CHECK  ;

void loop(void);

#endif