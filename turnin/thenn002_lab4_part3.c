/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Lock, Unlock1, Unlock2} state;

void Tick() {
	switch(state) {
		case Start:
			state = Lock;
			break;
		case Lock:
			if(PINA == 0x04) { state = Unlock1; }
			break;
		case Unlock1:
			if(PINA == 0x02) { state = Unlock2; }
			else if(PINA == 0x00) { state = Unlock1; }
			else if(PINA == 0x04) { state = Unlock1; }
			else { state = Lock; }
			break;
		case Unlock2:
			if(PINA == 0x80) { state = Lock; }
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
                case Start:
                        break;
                case Lock:
		case Unlock1:
			PORTB = 0x00;
			break;
		case Unlock2:
                        PORTB = 0x01;
                        break;
		default:
			break;
        }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	state = Start;
	while (1) { Tick(); }
	return 1;
}
