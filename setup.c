#include	"main.h"
#include	"Timer.h"
//#include	"INT.h"
#include	"GPIO.h"
//#include	"ADC.h"
#include	"OSC.h"
#include	"Loop.h"
//#include	"PWM.h"
//#include	"FVR.h"
//#include	"Serial595.h"
//#include	"Buzzer.h"
//#include	"TMR1GATE.h"
//#include	"EEPROM.h"

void setup(void)
{
	//GPIO Initial
	GPIO_Initial ( ) ;

	//Timer Initial
	Timer_Initial ( ) ;
}
