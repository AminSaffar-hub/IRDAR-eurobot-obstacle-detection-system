/*
 * balise_first_try.c
 *
 * Created: 7/4/2018 1:20:52 PM
 * Author : Amin Saffar
 */
 
//define clock speed
#define  F_CPU 16000000 



//libraries 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "USART.h"
#include "INTERRUPT.h"
#include "TIMER.h"
#include "IR.h"


FILE mystdout = FDEV_SETUP_STREAM(TransmitByte_IO, NULL,_FDEV_SETUP_WRITE);
FILE mystdin = FDEV_SETUP_STREAM(NULL, Receive_IO ,_FDEV_SETUP_READ);



int tsop[18]={2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};// PCINT of the receivers' pins buffer                                            
int stateBuff[18];																  // Difference between actual and last change time
int lastRecord;                                                           // Last time the data has been recorded
int nowRecord;                                                            // Actual recording data time
int deltaRecord;                                                          // Difference between actual and last time the data has been recorded
volatile int c1;                                                         // Counter 1
volatile int c2;
int c =0;


void communication(int irword,int stateBuff[]){
	int count=0,premier=0,centre=0;
	centre=0;
	count=counter( stateBuff , irword );
	if(count != 0) {
		premier=first( stateBuff , irword );
		centre=center( count , premier );
	}
	printf("%2d%2d",centre,count);
}


void communication2(int buff[] )
{
	printf("%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d\n",buff[0],buff[1],buff[2],buff[3],buff[4],buff[5],buff[6],buff[7],buff[8],buff[9],buff[10],buff[11],buff[12],buff[13],buff[14],buff[15],buff[16],buff[17]);
}

//main function 
int main(void){   
	//char c;
	InitUART(MYUBRR);
    init_Timer();
	init_PCInt();
	stdout = &mystdout;
	stdin = &mystdin;
	while (1) 
    {	//printf("1\n");
		for (int i = 0 ; i<18 ; i++)
		{
			stateBuff[i] = 0;
		}
		for(c2=0;c2<18;c2++)
		{  
			enable_PCI_interrupts (tsop[c2]);
			lastRecord=millis();
			do{
				nowRecord=millis();
				deltaRecord=nowRecord-lastRecord;
			   }while((deltaRecord<RECORD_TIME)&&((c1>=0)&&(c1<(RAWBUFF-9))));

			disable_PCI_interrupts();
			if(decodeIR(IR_WORD)==(IR_WORD)) stateBuff[c2]=ir_number; 
			initialisationRawBuff();
			
		}
		fillBlank(ir_number);
		c++;
		//communication2(stateBuff);
		communication(ir_number,stateBuff);
    }
}
