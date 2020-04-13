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

enum States{Start, Off, Switch1, Switch2, On} state;

void Tick() {
	switch(state) {
		case Start:
			state = Off;
			break;
		case Off:
			if(PINA == 0x01) { state = Switch1; }
			break;
		case Switch1:
			if(PINA == 0x00) { state = On; }
			break;
		case On:
			if(PINA == 0x01) { state = Switch2; }
			break;
		case Switch2:
			if(PINA == 0x00) { state = Off; }
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
                case Start:
                        break;
                case Off:
                        PORTB = 0x01;
                        break;
                case Switch1:
                        PORTB = 0x02;
                        break;
                case On:
                        PORTB = 0x02;
                        break;
                case Switch2:
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
