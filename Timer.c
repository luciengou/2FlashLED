#include	"main.h"
#include	"Timer.h"

static void TIM0_Init( uint8_t Tick )
{
	OPTION =0x90 | Tick ; 
}

void Timer_Initial(void)
{
  	TIM0_Init(0);	// 0~ 7 Prescaler Rate Select bits for Timer 0
					// 0 : 2 us
					// 1 : 4 us
					// 2 : 8 us
					// 3 : 16 us
					// 4 : 32 us
					// 5 : 64 us
					// 6 : 128 us
					// 7 : 256 us
  	
}
