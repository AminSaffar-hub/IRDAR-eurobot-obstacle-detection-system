/*
 * INTERRUPT.c
 *
 * Created: 12/21/2018 8:39:13 PM
 *  Author: Amin Saffar
 */ 
#include"INTERRUPT.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

void enable_PCI_interrupts (int i){
	
	switch(i)
	{
		case 2:
		PCMSK2 |= (1<<PCINT18);
		break;
		case 3:
		PCMSK2 |= (1<<PCINT19);
		break;
		case 4:
		PCMSK2 |= (1<<PCINT20);
		break;
		case 5:
		PCMSK2 |= (1<<PCINT21);
		break;
		case 6:
		PCMSK2 |= (1<<PCINT22);
		break;
		case 7:
		PCMSK2 |= (1<<PCINT23);
		break;
		case 8:
		PCMSK0 |= (1<<PCINT0);
		break;
		case 9:
		PCMSK0 |= (1<<PCINT1);
		break;
		case 10:
		PCMSK0 |= (1<<PCINT2);
		break;
		case 11:
		PCMSK0 |= (1<<PCINT3);
		break;
		case 12:
		PCMSK0 |= (1<<PCINT4);
		break;
		case 13:
		PCMSK0 |= (1<<PCINT5);
		break;
		case 14:;
		PCMSK1 |= (1<<PCINT8);
		break;
		case 15:
		PCMSK1 |= (1<<PCINT9);
		break;
		case 16:
		PCMSK1 |= (1<<PCINT10);
		break;
		case 17:
		PCMSK1 |= (1<<PCINT11);
		break;
		case 18:
		PCMSK1 |= (1<<PCINT12);
		break;
		case 19:
		PCMSK1 |= (1<<PCINT13);
		break;
	}
	
}
void init_PCInt(){
	//free all pending interrupts
	PCIFR |= (1<<PCIF0);
	PCIFR |= (1<<PCIF1);
	PCIFR |= (1<<PCIF2);
	//disable all PCints
	PCMSK0 = 0x00;
	PCMSK1 = 0x00;
	PCMSK2 = 0x00;
	//enable control register
	PCICR |= (1<<PCIE2)|(1<<PCIE1)|(1<<PCIE0);
}
void disable_PCI_interrupts(){
	PCIFR |= (1<<PCIF0);
	PCIFR |= (1<<PCIF1);
	PCIFR |= (1<<PCIF2);
	PCMSK0 = 0x00;
	PCMSK1 = 0x00;
	PCMSK2 = 0x00;
}
