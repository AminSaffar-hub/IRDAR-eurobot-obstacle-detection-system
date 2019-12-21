/*
 * CFile1.c
 *
 * Created: 12/21/2018 8:01:05 PM
 *  Author: Amin Saffar
 */ 
#include"USART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


//USART vars
static unsigned char UART_RxBuf[UART_RX_BUFFER_SIZE];
static volatile unsigned char UART_RxHead;
static volatile unsigned char UART_RxTail;
static unsigned char UART_TxBuf[UART_TX_BUFFER_SIZE];
static volatile unsigned char UART_TxHead;
static volatile unsigned char UART_TxTail;


ISR(USART_RX_vect){
	unsigned char data;
	unsigned char tmphead;
	
	/* Read the received data */
	data = UDR0;
	/* Calculate buffer index */
	tmphead = (UART_RxHead + 1) & UART_RX_BUFFER_MASK;
	/* Store new index */
	UART_RxHead = tmphead;

	if (tmphead == UART_RxTail) {
		/* ERROR! Receive buffer overflow */
	}
	/* Store received data in buffer */
	UART_RxBuf[tmphead] = data;
}
ISR(USART_UDRE_vect){
	unsigned char tmptail;

	/* Check if all data is transmitted */
	if (UART_TxHead != UART_TxTail) {
		/* Calculate buffer index */
		tmptail = ( UART_TxTail + 1 ) & UART_TX_BUFFER_MASK;
		/* Store new index */
		UART_TxTail = tmptail;
		/* Start transmission */
		UDR0 = UART_TxBuf[tmptail];
		} else {
		/* Disable UDRE interrupt */
		UCSR0B &= ~(1<<UDRIE0);
	}
}
void InitUART(unsigned char ubrr_val)
{
	unsigned char x;
	/* Set the baud rate */
	UBRR0H = (unsigned char)(ubrr_val>>8);
	UBRR0L = (unsigned char)ubrr_val;
	/* Enable UART receiver and transmitter */
	UCSR0B = ((1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0));
	// Set frame format: 8data, 1 stop bit
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	
	/* Flush receive buffer */
	x = 0;

	UART_RxTail = x;
	UART_RxHead = x;
	UART_TxTail = x;
	UART_TxHead = x;
}
void TransmitByte(unsigned char data){
	unsigned char tmphead;
	
	/* Calculate buffer index */
	tmphead = (UART_TxHead + 1) & UART_TX_BUFFER_MASK;
	/* Wait for free space in buffer */
	while (tmphead == UART_TxTail);
	/* Store data in buffer */
	UART_TxBuf[tmphead] = data;
	/* Store new index */
	UART_TxHead = tmphead;
	/* Enable UDRE interrupt */
	UCSR0B |= (1<<UDRIE0);
}
unsigned char Receive_IO(FILE *stream)
{
	unsigned char tmptail;
	/* Wait for incoming data */
	if(UART_RxHead != UART_RxTail)
	{
		/* Calculate buffer index */
		tmptail = (UART_RxTail + 1) & UART_RX_BUFFER_MASK;
		/* Store new index */
		UART_RxTail = tmptail;
		/* Return data */
		return UART_RxBuf[tmptail];
	}
	else
	return 1 ;
}
int TransmitByte_IO(char data,FILE *stream){
	unsigned char tmphead;
	if (data  == '\n')
	TransmitByte_IO('\r', stream);
	/* Calculate buffer index */
	tmphead = (UART_TxHead + 1) & UART_TX_BUFFER_MASK;
	/* Wait for free space in buffer */
	while (tmphead == UART_TxTail);
	/* Store data in buffer */
	UART_TxBuf[tmphead] = data;
	/* Store new index */
	UART_TxHead = tmphead;
	/* Enable UDRE interrupt */
	UCSR0B |= (1<<UDRIE0);
	return 0;
}
