#include "main.h"
#include "Timer.h"

__CONFIG(OSC_IntRC & WDT_OFF & CP_OFF & MCLRE_OFF);

void GPIO_Initial(void)
{
	TRISGPIO = 0x8F ;	// 1000 1111
   						// RA0 = Mode Select 1
						// RA1 = Mode Select 2
						// RA2 = Mode Select 3
						// RA3 = ServoIn    (Input) MCLR
						// RA4 = LED 1
						// RA5 = LED 2	
}

void Timer_Initial(uint8_t	PreScaler )
{
	OPTION = 0 ;
	OPTION =0x90 | PreScaler ;	// 7: /GPWU = 1 
								// 6: /GPPU = 0
								// 5:  T0CS = 0
								// 4:  T0SE = 1
								// 3:  PSA  = 0
								// 2-0 : Prescaler
}								

void setup(void)
{
	//GPIO Initial
	GPIO_Initial ( ) ;

	//Timer Initial
	Timer_Initial ( 3 ) ;	// 0~ 7 Prescaler Rate Select bits for Timer 0
							// 0 : 2 us , Overflow at 512us     ,  0.512ms	
							// 1 : 4 us	, Overflow at 1024us    ,  1.024ms	
							// 2 : 8 us , Overflow at 2048us	,  2.048ms	
							// 3 : 16 us , Overflow at 4096us	,  4.096ms
							// 4 : 32 us , Overflow at 8192us   ,  8.192ms
							// 5 : 64 us , Overflow at 16384us  , 16.384ms		
							// 6 : 128 us , Overflow at 32768us , 32.796ms
							// 7 : 256 us , Overflow at 65536us , 65.536ms
}

void Read_Mode ( void )
{
	uint8_t temp_mode ;
	
	//temp_mode = GPIO  ;	
	//__delay_ms(500);

	temp_mode = GPIO  ;
	temp_mode = temp_mode & 0x07 ;	// 0000 0111 , GP2 GP1 GP0
	
	switch ( temp_mode )
	{
		case 0x07 :		// 0000 0111
		
			Flash_Mode = 0 ;
			
			break ;
			
		case 0x06 :		// 0000 0110
		
			Flash_Mode = 1 ;
			
			break ;
			
		case 0x05 :		// 0000 0101
		
			Flash_Mode = 2 ;	
			
			break ;
			
		case 0x04 :		// 0000 0100
		
			Flash_Mode = 3 ;
			
			break ;
			
		case 0x03 :		// 0000 0011
		
			Flash_Mode = 4 ;
			
			break ;
			
		case 0x02 :		// 0000 0010
		
			Flash_Mode = 5 ;
			
			break ;
			
		case 0x01 :		// 0000 0001
		
			Flash_Mode = 6 ;
			
			break ;
			
		case 0x00 :		// 0000 0000
		
			Flash_Mode = 7 ;
			
			break ;

		default :
		
			Flash_Mode = 0 ;
	}
	
}
void LED_Flash_Times ( uint8_t LTimes )
{
	uint8_t Flash_Times , Flash_LEDs ;
	
	Flash_LEDs = LTimes >> 4 ;
	Flash_Times = LTimes & 0x0F ;
	
	while ( Flash_Times-- )
	{
		switch ( Flash_LEDs )
		{
			case 0 :
				LED1 = LED_Flash ;
				LED2 = LED_Flash ;
				
				break ;
				
			case 1 :
				LED1 = LED_Flash ;
				LED2 = LED_Dark ;
				
				break ;
				
			case 2 :
				LED1 = LED_Dark ;
				LED2 = LED_Flash ;
				
				break ;
		}
		
		__delay_ms(Flash_Time_Short1);
		
		LED1 = LED_Dark ;
		LED2 = LED_Dark ;	
		
		__delay_ms(Flash_Time_Short);
	}

}	
void main(void)
{
	setup();
	
	__delay_ms(500);
	
while(1)
{
	if ( Flash_Mode < 5 ) Read_Mode() ;
	else if ( ( low_time == 1 ) || ( high_time == 1 ) ) Read_Mode() ;

	//Flash_Mode = 5 ;	

	if ( high_time == 1 )
	{
		// Wait for High
		Timer_Initial ( 6 ) ;	// 0~ 7 Prescaler Rate Select bits for Timer 0
								// 0 : 2 us , Overflow at 512us     ,  0.512ms	
							// 1 : 4 us	, Overflow at 1024us    ,  1.024ms	
							// 2 : 8 us , Overflow at 2048us	,  2.048ms	
							// 3 : 16 us , Overflow at 4096us	,  4.096ms
							// 4 : 32 us , Overflow at 8192us   ,  8.192ms
							// 5 : 64 us , Overflow at 16384us  , 16.384ms		
							// 6 : 128 us , Overflow at 32768us , 32.768ms
							// 7 : 256 us , Overflow at 65536us , 65.536ms
		TMR0 = 0 ;	
		while ( ServoIn == 0 && TMR0 < 255) ;	// "/" wait for 32ms , normal ServoIn Low < 20ms
		Servo_Pulse_Width = TMR0 ;
	
		if (Servo_Pulse_Width < 156 ) // ServoIn low < 20ms
		{
			// Wait for Low
			Timer_Initial ( 3 ) ;
			TMR0 = 0 ;
			while ( ServoIn == 1 && TMR0 < 254 ) ;	// "\"
			Servo_Pulse_Width = TMR0 ;
	
			if ( Servo_Pulse_Width < 65 && Servo_Pulse_Width > 31 )
										//1ms=63 at 0%, 2ms= 127 at 100% , 0.5ms~1.25ms is correct pulse width
			{								//1.25ms=63+16 at 25% , 1.75ms=63+48 at 75%
				Flash_Mode = 99 ;
			}
			//__delay_ms( 12 );
		}
	}	
	
	switch ( Flash_Mode )
		{
			
			case 0 :							// Mode Setting aaaa bbbb : "aaaa" is Flash Mode , "bbbb" is Flash Times
				LED_Flash_Times( 0x01 );		// Mode 0 : LED1 and LED2 Flash the same time
				__delay_ms(Flash_Time_Next);	// Flash Time : 1
		
				break ; 
		
			case 1 :
				LED_Flash_Times( 0x02 );		// Mode 0 : LED1 and LED2 Flash the same time
				__delay_ms(Flash_Time_Next);	// Flash Time : 2
				break ;
				
			case 2 :
				LED_Flash_Times( 0x05 );		// Mode 0 : LED1 and LED2 Flash the same time
				__delay_ms(Flash_Time_Next);	// Flash Time : 5
				break ; 
		
			case 3 :		
				LED_Flash_Times( 0x11 );		// Mode 1 : LED1 Flash First
				__delay_ms(Flash_Time_Next);	// Flash Time : 1
				LED_Flash_Times( 0x21 );		// Mode 2 : LED2 Flash First
				__delay_ms(Flash_Time_Next);
			
				break ; 

			case 4 :
				LED_Flash_Times( 0x15 );		// Mode 1 : LED1 Flash First , LED2 Dark
				__delay_ms(Flash_Time_Next);	// Flash Time : 5
				LED_Flash_Times( 0x25 );		// Mode 2 : LED2 Flash First , LED1 Dark
				__delay_ms(Flash_Time_Next);	// Flash Time : 5

				break ; 
		
			case 5 :
				if ( high_time < 5 || high_time > 250)	// LED1 and LED2 is Breath LED ,and no Flash
					loop_time = 20 ;
				else
					loop_time = 3 ;
			
				while ( loop_time-- )
				{
					LED1 = LED_Flash ;
					LED2 = LED_Flash ;
				
					led_delay = high_time ;
					while ( led_delay -- ) __delay_us(6) ;
			
			
					LED1 = LED_Dark ;
					LED2 = LED_Dark ;
				
					led_delay = low_time ;
					while ( led_delay -- ) __delay_us(6) ;
 
				}
				
				if ( high_time == 1 ) Breath_Mode = 0 ;

				if ( low_time == 1  ) Breath_Mode = 1 ;
					
				if ( Breath_Mode )
				{						
					high_time -- ;	low_time ++ ;
				}
				else
				{
					high_time ++ ; 	low_time -- ;
				}
	
				break ;
			
			case 6 :										// LED1 and LED2 is Breath LED and Flash the same time
				//while ( high_time > 1 )
				{
					//if ( high_time < 5 || high_time > 250)
					//	loop_time = 20 ;
					//else
						loop_time = 2 ;
				
					while ( loop_time-- )
					{
						LED1 = LED_Flash ;
						LED2 = LED_Flash ;
				
						led_delay = high_time ;
						while ( led_delay -- ) __delay_us(6) ;
				
						LED1 = LED_Dark ;
						LED2 = LED_Dark ;
				
						led_delay = low_time ;
						while ( led_delay -- ) __delay_us(6) ;
					}
			
					if ( high_time == 1 )
					{
						Breath_Mode = 0 ;
						
						LED1 = LED_Dark ;	LED2 = LED_Dark ;
						
						__delay_ms(500);
			
						LED1 = LED_Flash ;  LED2 = LED_Flash ;

						__delay_ms(Flash_Time_Short);
				
						LED1 = LED_Dark ;	LED2 = LED_Dark ;
						
						__delay_ms(500);
					}
					if ( low_time == 1 ) Breath_Mode = 1 ;
			
					if ( Breath_Mode )
					{
						high_time -- ;
						low_time ++ ;
					}
					else
					{
						high_time ++ ;
						low_time -- ;
					}
				}
				break ;
			
			case 7 :							// LED1 and LED2 is Breath LED and Flash Change 
				//while ( high_time > 0 )
				{
					//if ( high_time < 5 || high_time > 249)
					//	loop_time = 30 ;
					//else
						loop_time = 2 ;
					
					while ( loop_time-- )
					{
						LED1 = LED_Flash ;
						LED2 = LED_Dark ;
				
						led_delay = high_time ;
						while ( led_delay -- ) __delay_us(6) ;
				
						LED1 = LED_Dark ;
						LED2 = LED_Flash ;
				
						led_delay = low_time ;
						while ( led_delay -- ) __delay_us(6) ;
					}
			
					if ( high_time == 1 ) Breath_Mode = 0 ;
					if ( low_time == 1  ) Breath_Mode = 1 ;
			
					if ( Breath_Mode )
					{
						high_time -- ;
						low_time ++ ;

					}
					else
					{
						high_time ++ ;
						low_time -- ;
					}
				}
				break ;	
			case 99 :
				LED1 = LED_Dark ;		
				LED2 = LED_Dark ;
			
		}
	}	
}




