#include	"main.h"
#include	"Timer.h"

void delay_1s(void)
{
#ifndef	Hardware_Delay
	__delay_ms(1000);
#else
	uint16_t ms = 0 ;
	
	while ( ms < 1000 )		// Delay 1s
	{
		TMR0 = 0 ;
		while( TMR0 < 250 ) ;
		ms ++ ;
	}
#endif
}
void delay_500ms(void)
{
#ifndef	Hardware_Delay
	__delay_ms(500);
#else
	uint16_t ms = 0 ;
	
	while ( ms < 500 )		// Delay 0.5s
	{
		TMR0 = 0 ;
		while( TMR0 < 250 ) ;
		ms ++ ;
	}
#endif
}
void delay_ms(uint16_t ms)
{
	while(ms--){
#ifndef	Hardware_Delay
		__delay_ms(1);
#else
		TMR0 = 0 ;
		while( TMR0 < 250 ) ;
#endif
	}
}
void delay_1ms(void)
{
#ifdef	Hardware_Delay
	TMR0 = 0 ;
	while( TMR0 < 250 ) ;
#else
	__delay_ms(1);
#endif
}

void delay_1us(void)
{
	__delay_us(1);
}

void delay_us(uint16_t us)
{
	while ( us-- )
		__delay_us(1);
}	
