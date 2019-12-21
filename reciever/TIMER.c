/*
 * TIMER.c
 *
 * Created: 12/22/2018 8:52:05 AM
 *  Author: Amin Saffar
 */ 
#include "TIMER.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/atomic.h>


//timer variables
volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;



ISR(TIMER0_OVF_vect){
	unsigned long m = timer0_millis;
	unsigned char f = timer0_fract;

	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;
}
void init_Timer(){
	//prescaler = 64
	TCCR0B  |= (1<<CS01)|(1<<CS00);
	//mask enable
	TIMSK0 |=(1<<TOIE0);
	//allow global interrupts
	sei();
}

unsigned long micros(){
	unsigned long m;
	//ATOMIC_BLOCK(ATOMIC_FORCEON) {
		m = ((timer0_overflow_count << 8) + TCNT0) * (64 / 16);
	//}
	return (m);
}
unsigned long millis(){
	unsigned long m;
	//ATOMIC_BLOCK(ATOMIC_FORCEON) {
		m = timer0_millis;
	//}
	return m;
}
