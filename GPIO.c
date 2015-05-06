#include	"main.h"
#include	"GPIO.h"

void GPIO_Initial(void)
{
   	GPIObits.GP0 = 1;	// RA0 = Mode Select 1
    GPIObits.GP1 = 1;	// RA1 = Mode Select 2
    GPIObits.GP2 = 0;	// RA2 = LED 1
    GPIObits.GP3 = 1;	// RA3 = ServoIn    (Input) MCLR
    GPIObits.GP4 = 1;	// RA4 = Mode Select 3
    GPIObits.GP5 = 0;	// RA5 = LED 2	
}
