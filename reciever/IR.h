/*
 * IncFile1.h
 *
 * Created: 7/13/2018 11:59:51 PM
 *  Author: Amin Saffar
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#include <stdio.h>

#define  balise_1
//#define  balise_2

//IR macros macros
#define JVC_HDR_MARK 1500                                                 // Start bit High = 3000us
#define JVC_BIT_MARK 250                                                 // Data bit High for 1/0 = 500us
#define JVC_ONE_SPACE 500                                                // Data bit Low for 1 = 1000us
#define JVC_ZERO_SPACE 250                                                // Data bit Low for 0 = 500us
#define JVC_RPT_LENGTH 3500                                           // Rest time = 30000us
#define TOLERANCE 25                                                      // Percent tolerance in measurements
#define LTOL (1.0 - TOLERANCE/100.0)                                       // Least float tolerance in measurments
#define UTOL (1.0 + TOLERANCE/100.0)                                       // Upper float tolerance in measurments
#define TOPBIT 0x80000000                                                 // Mask to extract the top bit
//#define BITS (int) (3*2)                                                // Bits number in Data
#define BITS (int) (2*2)                                                // Bits number in Data
//#define RECORD_TIME 30
#define RECORD_TIME 20                                      // Recording data time = 30ms                                                 // Recording data time = 30ms
#define TICKS_LOW(us) (int) (((us)*LTOL))                                 // Lower value allowed
#define TICKS_HIGH(us) (int) (((us)*UTOL))                                // Highest value allowed
#define RAWBUFF 21




#ifdef balise_1
	#define IR_WORD 0x1
	#define ir_number 1
#endif

#ifdef balise_2
	#define IR_WORD 0x2
	#define ir_number 2
#endif


int decodeIR(int word);
void initialisationRawBuff();
void fillBlank(int n);
int counter(int T[18], int n);
int first(int T[18], int n);
int center(int nb, int first);
void clear_buffs();


#endif /* INCFILE1_H_ */