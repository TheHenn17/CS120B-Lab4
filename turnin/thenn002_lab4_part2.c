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

enum States{Start, Wait, Inc, Dec, Rst} state;
unsigned char cnt;

void Tick() {
	switch(state) {
		case Start:
			state = Wait;
			break;
		case Wait:
			if(PINA == 0x01) {
				state = Inc;
				if(cnt < 9) { cnt++; }
			}
			else if(PINA == 0x02) {
				state = Dec;
				if(cnt > 0) { cnt--; }
		       	}
			else if(PINA == 0x03) {
				state = Rst;
				cnt = 0;
			}
			break;
		case Inc:
			if(PINA == 0x00) { state = Wait; }
			else if(PINA == 0x02) {
				state = Dec;
				if(cnt > 0) { cnt--; }
			}
			else if(PINA == 0x03) {
				state = Rst;
				cnt = 0;
			}
			break;
		case Dec:
			if(PINA == 0x00) { state = Wait; }
			else if(PINA == 0x01) {
				state = Inc;
				if(cnt < 9) { cnt++; }
			}
			else if(PINA == 0x03) {
				state = Rst;
				cnt = 0;
			}
			break;
		case Rst:
			if(PINA == 0x00) { state = Wait; }
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
                case Start:
                        break;
                case Wait:
		case Inc:
		case Dec:
		case Rst:
                        PORTC = cnt;
                        break;
		default:
			break;
        }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	state = Start;
	cnt = 7;
	while (1) { Tick(); }
	return 1;
}
