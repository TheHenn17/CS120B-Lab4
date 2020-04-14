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

enum States{Start, Locked, Unlocked, CheckU, CheckL, IncU, IncL} state;
unsigned char sequence[] = { 4, 1, 2, 1 };
unsigned char i;

void Tick() {
	switch(state) {
		case Start:
			state = Locked;
			break;
		case Locked:
			i = 0;
			if(PINA == sequence[i]) { state = IncU; }
			break;
		case IncU:
			if(PINA == 0x00) {
				i++;
				state = CheckU;
			}
			break;
		case CheckU:
			if(i == 4) { state = Unlocked; }
			else if(PINA == 0x00) { state = CheckU; }
			else if(PINA == sequence[i]) { state = IncU; }
			else { state = Locked; }
			break;
		case Unlocked:
			i = 0;
			if(PINA == 0x80) { state = Locked; }
			else if(PINA == sequence[i]) { state = IncL; }
                        break;
		case IncL:
			if(PINA == 0x00) {
                                i++;
                                state = CheckL;
                        }
                        break;
		case CheckL:
			if(i == 4) { state = Locked; }
                        else if(PINA == 0x00) { state = CheckL; }
                        else if(PINA == sequence[i]) { state = IncL; }
			else if(PINA == 0x80) { state = Unlocked; }
                        else { state = Unlocked; }
                        break;
		default:
			state = Start;
			break;
	}
	switch(state) {
		case Start:
                        break;
                case Locked:
		case IncU:
		case CheckU:
			PORTB = 0x00;
                        break;
                case Unlocked:
                case IncL:
                case CheckL:
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
