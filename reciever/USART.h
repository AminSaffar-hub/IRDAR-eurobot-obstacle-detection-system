/*
 * USART_.h
 *
 * Created: 12/21/2018 8:00:47 PM
 *  Author: Amin Saffar
 */ 


#ifndef USART_H_
#define USART_H_

#include <stdio.h>



#define F_CPU 16000000


//USART macros
#define FOSC 16000000 // Clock Speed
#define BAUD 57600
#define MYUBRR (((F_CPU / (BAUD * 16UL))) - 1)


/* UART Buffer Defines */
#define UART_RX_BUFFER_SIZE 8     /* 2,4,8,16,32,64,128 or 256 bytes */
#define UART_TX_BUFFER_SIZE 8
#define UART_RX_BUFFER_MASK (UART_RX_BUFFER_SIZE - 1)

#if (UART_RX_BUFFER_SIZE & UART_RX_BUFFER_MASK)
#error RX buffer size is not a power of 2
#endif

#define UART_TX_BUFFER_MASK (UART_TX_BUFFER_SIZE - 1)
#if (UART_TX_BUFFER_SIZE & UART_TX_BUFFER_MASK)
#error TX buffer size is not a power of 2
#endif



//usart functions headers 
void InitUART(unsigned char ubrr_val);
void TransmitByte(unsigned char data);
unsigned char Receive_IO(FILE *stream);
int TransmitByte_IO(char data,FILE *stream);





#endif /* USART _H_ */