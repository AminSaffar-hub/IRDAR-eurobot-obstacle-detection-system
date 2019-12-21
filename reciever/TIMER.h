/*
 * TIMER.h
 *
 * Created: 12/22/2018 8:51:43 AM
 *  Author: Amin Saffar
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include <stdio.h>


#define F_CPU 16000000



//timer macros
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (F_CPU / 1000L) )
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

// function headers
void init_Timer();
unsigned long millis();
unsigned long micros();



#endif /* TIMER_H_ */