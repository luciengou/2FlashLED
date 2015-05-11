#ifndef __main_H_

#define	__main_H_

#ifdef __PICC__
#include	<htc.h> 
#else
#include	<xc.h> 
#endif
#include	<stdint.h>

#define _XTAL_FREQ 4000000

// Oscillator / resonator frequency (in Hz) e.g. (11059200UL)
//#define OSC_FREQ (4000000UL)

// Number of oscillations per instruction (12, etc)
// 12 - Original 8051 / 8052 and numerous modern versions
//  6 - Various Infineon and Philips devices, etc.
//  4 - Dallas 320, 520 etc.
//  1 - Dallas 420, etc.
//#define OSC_PER_INST (4)

/*!< Signed integer types  */
typedef signed char     int8_t;
typedef signed short    int16_t;
typedef signed long     int32_t;

/*!< Unsigned integer types  */
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;

#define	ON		1
#define OFF		0
#define	YES		1
#define NO		0
#define	HIGH	1
#define LOW 	0
#define MS1		GPIObits.GP0	// RA0 = Mode Select 1
#define MS2		GPIObits.GP1 	// RA1 = Mode Select 2
#define MS3     GPIObits.GP2	// RA2 = Mode Select 3
#define ServoIn GPIObits.GP3	// RA3 = ServoIn    (Input) MCLR
#define LED1	GPIObits.GP4 	// RA4 = LED 1
#define LED2	GPIObits.GP5	// RA5 = LED 2

#define LED_Flash	1
#define LED_Dark	0
#define Flash_Time_Short3 10
#define Flash_Time_Short2 20
#define Flash_Time_Short1 30
#define Flash_Time_Short 40

#define Flash_Time_Long	 200
//#define Flash_Time_Next	 268
#define Flash_Time_Next	 500

//#define	Hardware_Delay

uint8_t Flash_Mode ;
uint8_t led_delay , high_time = 1 , low_time = 0xFF , Breath_Mode = 0 ;
uint8_t loop_time ;
uint8_t	Servo_Pulse_Width ;


#endif