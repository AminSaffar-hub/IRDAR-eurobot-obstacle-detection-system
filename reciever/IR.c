/*
 * CFile1.c
 *
 * Created: 7/14/2018 12:03:20 AM
 *  Author: Amin Saffar
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "IR.h"
#include "TIMER.h"
#include <stdio.h>

//variables                                                     // Receivers' state buffer
int stateBuff[18];
volatile int rawBuff[RAWBUFF];                                            // Raw duration buffer
volatile int lastTime;                                                    // Last change time
volatile int nowTime;                                                     // Actual change time
volatile int deltaTime;                                                   // Difference between actual and last change time                                                     // Difference between actual and last time the data has been recorded
volatile int c1;                                                         // Counter 1
volatile int c2;

ISR(PCINT1_vect)
{
	nowTime=micros();
	if(c1>RAWBUFF) c1=0;
	deltaTime=nowTime-lastTime;
	lastTime=nowTime;
	if((deltaTime>=TICKS_LOW(JVC_HDR_MARK))&&(deltaTime<=TICKS_HIGH(JVC_HDR_MARK))&&(!c1)){
		
		c1=1;
		rawBuff[c1]=deltaTime;
		c1++;
		
		
	}
	else if((c1>1)&&(c1<(RAWBUFF-5))&& (deltaTime < 15000)){
		rawBuff[c1]=deltaTime;
		c1++;
	}
}
ISR(PCINT2_vect)
{
	nowTime=micros();
	if(c1>RAWBUFF) c1=0;
	deltaTime=nowTime-lastTime;
	lastTime=nowTime;
	if((deltaTime>=TICKS_LOW(JVC_HDR_MARK))&&(deltaTime<=TICKS_HIGH(JVC_HDR_MARK))&&(!c1)){
		c1=1;
		rawBuff[c1]=deltaTime;
		c1++;
	}
	else if((c1>1)&&(c1<(RAWBUFF-5))){
		rawBuff[c1]=deltaTime;
		c1++;
	}
}
ISR(PCINT0_vect)
{
	nowTime=micros();
	if(c1>RAWBUFF) c1=0;
	deltaTime=nowTime-lastTime;
	lastTime=nowTime;
	if((deltaTime>=TICKS_LOW(JVC_HDR_MARK))&&(deltaTime<=TICKS_HIGH(JVC_HDR_MARK))&&(!c1)){
		c1=1;
		rawBuff[c1]=deltaTime;
		c1++;
	}
	else if((c1>1)&&(c1<(RAWBUFF-5))){
		rawBuff[c1]=deltaTime;
		c1++;
	}
}
int decodeIR(int word){
	int code=0;
	int codef=0;
	int bits=0;
	int j;
	for(bits=0;bits<(RAWBUFF-10);bits++){
		code=0;
		while((rawBuff[bits]<TICKS_LOW(JVC_HDR_MARK))||(rawBuff[bits]>TICKS_HIGH(JVC_HDR_MARK))){
			bits++;
		}
		if((rawBuff[bits]>=TICKS_LOW(JVC_HDR_MARK))&&(rawBuff[bits]<=TICKS_HIGH(JVC_HDR_MARK))){
			bits++;
			for(j=bits;j<(bits+BITS);j+=2){
				if((rawBuff[j]>=TICKS_LOW(JVC_ONE_SPACE))&&(rawBuff[j]<=TICKS_HIGH(JVC_ONE_SPACE))){
					code+=1;
					code = code << 1;
				}
				else if((rawBuff[j]>=TICKS_LOW(JVC_ZERO_SPACE))&&(rawBuff[j]<=TICKS_HIGH(JVC_ZERO_SPACE))){
					code = code << 1;
				}
				else{
					code = -1;
					break;
				}
			}
			code = code >> 1;
			if(code == word) {
				codef=code;
				return codef;
			}
			bits=j;
		}
	}
	return codef;
}
void initialisationRawBuff(){
	for(int i=0;i<RAWBUFF;i++){
		rawBuff[i]=0;
	}
	c1=0;
}

void fillBlank(int n){
	for(int i=18;i<36;i++){
		if((stateBuff[i%18]==0)&&((((stateBuff[(i-1)%18]==n)&&(stateBuff[(i+1)%18]==n))||
		((stateBuff[(i-1)%18]==n)&&(stateBuff[(i+1)%18]==0)&&stateBuff[(i+2)%18]==n))||
		((stateBuff[(i-2)%18]==n)&&(stateBuff[(i-1)%18]==0)&&(stateBuff[(i+1)%18]==n)))){
			stateBuff[i%18]=n;
		}
	}
}

int counter(int T[18], int n){
	int c=0;
	for(int i=0;i<18;i++){
		if(T[i]==n) c++;
	}
	return c;
}
int first(int T[18], int n){
	int i=18;
	if(T[i%18]==n){
		while(T[i%18]==n){
			i--;
		}
		i++;
	}
	else{
		while(T[i%18]==0){
			i++;
		}
	}
	return (i%18);
}
int center(int nb, int first){
	return((first+(nb/2))%18);
}
void clear_buffs()
{
	for (int i = 0 ; i<18 ; i++)
	{
		stateBuff[i] = 0;
	}
}


