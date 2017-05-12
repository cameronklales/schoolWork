

/*
 * LabFinal.c
 *
 * Created: 5/1/2017 1:26:51 PM
 * Author : Cameron
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD_driver.h"
#include <util/delay.h>

#define PINB_MASK ((1<<PINB4)|(1<<PINB6)|(1<<PINB7)) //easy to use masks
#define PINE_MASK ((1<<PINE2)|(1<<PINE3)) 


 /* setup */
	unsigned char count = 0; //set count variable to initial value zero
	volatile unsigned char mode = 3; //keeps track of last button pushed, 3 is default case(hold)
					/* Mode Values
					mode = 1, joystick up
					mode = 2, joystick down
					mode = 3, joystick center
					mode = 4, joystick left
					mode = 5, joystick right
					*/
	volatile char str [100]; 

	
int main(void)
{
// three buttons of joystick pins with pullup resistors
PORTB |= (1<<4)|(1<<7)|(1<<6);
PORTE |= ((1<<2)|(1<<3));


LCD_Init();// initialize the LCD
// enable interrupts
PCMSK1 |= PINB_MASK;
PCMSK0 |= PINE_MASK;
EIMSK |= (1<<PCIE1);
EIMSK |= (1<<PCIE0);
sei();// enable global interrupt

LCD_Init(); // Initialize LCD
sei(); // Enable global interrupts


	while(1){
		
		if (mode == 1) // joystick is up
		{
			count = count + 1; //increment count
			
		}
			
		if (mode == 2)
		{
			if (count >1)
			{
				count--;
			}else{
				count = 100;
			}
		}
		if (mode == 3)
		{
			count = count;
		}
		if (mode == 4)
		{
			if ((count%2) == 1)
			{
				count++;
			}
			count += 2;
		}
		if (mode == 5)
		{
		if ((count%2) == 0)
			{
				count++;
			}
			count += 2;
		}
		if (count > 100)
		{
			count = 0;
		}
		sprintf(str,"%d",count);
		LCD_puts(str);
		_delay_ms(1000);
		
		}
return 0;
}

ISR(PCINT1_vect,ISR_BLOCK) {
char joystick;// joystick port

joystick = ~PINB & ((1<<4)|(1<<7)|(1<<6));// read the port and mask it

if (joystick == (1<<4)) {       // if center pressed toggle flag
mode = 3;
return;// and return
}
if (joystick == (1<<7)) {      // if DOWN pressed toggle flag
mode = 2;
return;// and return
}
if (joystick == (1<<6)) {      // if UP pressed toggle flag
mode = 1;
return;// and return
}

if (joystick == 0) return;// if nothing pressed, return doing nothing

}

ISR(PCINT0_vect,ISR_BLOCK) {
char joystick;// joystick port

joystick = ~PINE & ((1<<2)|(1<<3));// read the port and mask it

if (joystick == (1<<2) ){       // if center pressed toggle flag
mode = 4;
return;// and return
}
if (joystick == (1<<3)) {      // if DOWN pressed toggle flag
mode = 5;
return;// and return

}

if (joystick == 0) return;// if nothing pressed, return doing nothing

}























